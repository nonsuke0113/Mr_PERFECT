//
//  EnemySprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/11/08.
//

#include "EnemySprite.hpp"
#include "StageSceneBase.hpp"
#include <algorithm>
#include <unistd.h>

#pragma mark -
#pragma mark init
/**
    CharacterSprite::createメソッドをオーバーライド
 
    @param filename 敵キャラクターの画像リソース名
    @param pos 敵キャラクターのワールド座標初期位置
    @param direction 敵キャラクターの向き
    @param moveSpeed 敵キャラクターの移動速度
    @return 敵キャラクターのSprite
 */
EnemySprite* EnemySprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float moveSpeed)
{
    EnemySprite *sprite =  new (std::nothrow) EnemySprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, moveSpeed)) {
        sprite->autorelease();
        return sprite;
    }
    return nullptr;
}


/**
    初期化処理
 
    @param filename 敵キャラクターの画像リソース名
    @param pos 敵キャラクターのワールド座標初期位置
    @param direction 敵キャラクターの向き
    @param moveSpeed 敵キャラクターの移動速度
 */
bool EnemySprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed)
{
    if (!CharacterSprite::initWithFileName(filename, pos, direction, moveSpeed)) {
        return false;
    }
    this->m_rotateDirectcion = ::turn_right;
    return true;
}


/**
    アニメーションキャッシュを作成する
 */
void EnemySprite::setupAnimationCache()
{
    Rect rect = Rect(0, 0, PER_TILE_SIZE, PER_TILE_SIZE);
    
    Animation *animationPlayerFront = Animation::create();
    animationPlayerFront->addSpriteFrame(SpriteFrame::create("enemy1_front1.png", rect));
    animationPlayerFront->addSpriteFrame(SpriteFrame::create("enemy1_front2.png", rect));
    animationPlayerFront->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerFront, "ENEMY_FRONT");
    
    Animation *animationPlayerRight = Animation::create();
    animationPlayerRight->addSpriteFrame(SpriteFrame::create("enemy1_right1.png", rect));
    animationPlayerRight->addSpriteFrame(SpriteFrame::create("enemy1_right2.png", rect));
    animationPlayerRight->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerRight, "ENEMY_RIGHT");
    
    Animation *animationPlayerBack = Animation::create();
    animationPlayerBack->addSpriteFrame(SpriteFrame::create("enemy1_back1.png", rect));
    animationPlayerBack->addSpriteFrame(SpriteFrame::create("enemy1_back2.png", rect));
    animationPlayerBack->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerBack, "ENEMY_BACK");
    
    Animation *animationPlayerLeft = Animation::create();
    animationPlayerLeft->addSpriteFrame(SpriteFrame::create("enemy1_left1.png", rect));
    animationPlayerLeft->addSpriteFrame(SpriteFrame::create("enemy1_left2.png", rect));
    animationPlayerLeft->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerLeft, "ENEMY_LEFT");
}


#pragma mark -
#pragma mark Setter
/**
    向きセッター
 */
void EnemySprite::setDirectcion(::directcion direction) {
    this->m_directcion = direction;
    
    Animation *animation = nullptr;
    switch (direction) {
        case front:
            animation = AnimationCache::getInstance()->getAnimation("ENEMY_FRONT");
            break;
        case right:
            animation = AnimationCache::getInstance()->getAnimation("ENEMY_RIGHT");
            break;
        case back:
            animation = AnimationCache::getInstance()->getAnimation("ENEMY_BACK");
            break;
        case left:
            animation = AnimationCache::getInstance()->getAnimation("ENEMY_LEFT");
            break;
        default:
            break;
    }
    
    if (animation == nullptr) {
        return;
    }
    this->stopActionByTag(animate);
    
    RepeatForever *action = RepeatForever::create( Animate::create(animation) );
    action->setTag(animate);
    this->runAction(action);
}


#pragma mark -
/**
    巡回をスケジュール
 */
void EnemySprite::startPatrol() {
    // 巡回をスケジュール
    schedule(schedule_selector(EnemySprite::rotatePatrol), 0.5f);
}


/**
    巡回を中止
 */
void EnemySprite::stopPatrol() {
    // 巡回を中止
    unschedule(schedule_selector(EnemySprite::rotatePatrol));
}


/**
    巡回する
    移動できないようになるまで、向いている方向でまっすぐ進む
    移動できなくなったら、設定された方向に回転する
 */
void EnemySprite::rotatePatrol(float frame) {
    
    if (this->checkFindPlayer()) {
        this->stopPatrol();
        StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
        mainScene->enemyFindPlayer();
    }
    
    if (this->nextTileGID() == 0) {
        this->moveNextTile();
    } else {
        this->rotate();
    }
}


/**
    設定された回転方向に応じて、向いている方向を変える
 */
void EnemySprite::rotate() {
    
    if (this->m_rotateDirectcion == ::turn_right) {
        switch (this->m_directcion) {
            case ::front:
                this->setDirectcion(::right);
                break;
            case ::right:
                this->setDirectcion(::back);
                break;
            case ::back:
                this->setDirectcion(::left);
                break;
            case ::left:
                this->setDirectcion(::front);
                break;
            default:
                break;
        }
    } else {
        switch (this->m_directcion) {
            case ::front:
                this->setDirectcion(::left);
                break;
            case ::right:
                this->setDirectcion(::front);
                break;
            case ::back:
                this->setDirectcion(::right);
                break;
            case ::left:
                this->setDirectcion(::back);
                break;
            default:
                break;
        }
    }
}


/**
    敵キャラクターが向いている方向に、プレイヤーがいるかどうかを確認する
 
    @return プレイヤーを発見したかどうか
 */
bool EnemySprite::checkFindPlayer() {
    
    Vec2 checkTilePosition;
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    CharacterSprite* player = mainScene->m_player;
    
    for (int i = 1; i < std::max(MAP_TILE_HEGHT, MAP_TILE_WIDTH); i++) {
        
        switch (this->m_directcion) {
            case ::front:
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + i };
                break;
            case ::right:
                checkTilePosition = Vec2 { this->m_worldPosition.x + i, this->m_worldPosition.y };
                break;
            case ::back:
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - i };
                break;
            case ::left:
                checkTilePosition = Vec2 { this->m_worldPosition.x - i, this->m_worldPosition.y };
                break;
            default:
                break;
        }
        
        if (!this->canMovePos(checkTilePosition)) {
            return false;
        }
        
        if (player->worldPosition() == checkTilePosition) {
            return true;
        }
    }
    
    return false;
}


/**
    現在地から目的地までの最短経路を探索する
    参照渡しにて経路のスタックを書き換える
 
    @param routeStack 現在の経路スタック
    @param shortestRouteStack 現在の最短経路スタック
    @param currentPos 現在地
    @param destinationPos 目的地
 */
void EnemySprite::searchShortestRoute(std::vector<Vec2>& routeStack,
                                      std::vector<Vec2>& shortestRouteStack,
                                      const Vec2& currentPos,
                                      const Vec2& destinationPos)
{
    // 現在地を経路スタックにプッシュ
    routeStack.push_back(currentPos);
    
    // ゴールしているかどうか
    if (currentPos == destinationPos) {
        // 最短経路であれば保存する
        if (shortestRouteStack.empty() || routeStack.size() < shortestRouteStack.size()) {
            shortestRouteStack = routeStack;
            routeStack.pop_back();
            return;
        }
    }
    
    // 既に最短経路の移動数を超えている場合、何もしない
    if (!shortestRouteStack.empty() && routeStack.size() >= shortestRouteStack.size()) {
        routeStack.pop_back();
        return;
    }
    
    // 経路探索
    // 上
    Vec2 upPos = Vec2 { currentPos.x, currentPos.y - 1.0f};
    if (this->canMovePos(upPos) && std::find(routeStack.begin(), routeStack.end(), upPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, upPos, destinationPos);
    }
    // 右
    Vec2 rightPos = Vec2 { currentPos.x + 1.0f, currentPos.y };
    if (this->canMovePos(rightPos) && std::find(routeStack.begin(), routeStack.end(), rightPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, rightPos, destinationPos);
    }
    // 下
    Vec2 downPos = Vec2 { currentPos.x, currentPos.y + 1.0f};
    if (this->canMovePos(downPos) && std::find(routeStack.begin(), routeStack.end(), downPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, downPos, destinationPos);
    }
    // 左
    Vec2 leftPos = Vec2 { currentPos.x - 1.0f, currentPos.y };
       if (this->canMovePos(leftPos) && std::find(routeStack.begin(), routeStack.end(), leftPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, leftPos, destinationPos);
    }

    routeStack.pop_back();
}


/**
    与えられた経路で移動を開始する
 
    @param routeStack 移動経路
 */
void EnemySprite::startMoveAccordingToRouteStack(const std::vector<Vec2>& routeStack)
{
    // 巡回は中断する
    this->stopPatrol();
    
    this->m_routeStack = new (std::nothrow) std::vector<Vec2>(routeStack);
    this->m_routeStackIndex = 0;
    schedule(schedule_selector(EnemySprite::moveAccordingToRouteStack), 0.5f);
}


/**
    経路に従う移動を停止する
 */
void EnemySprite::stopMoveAccordingToRouteStack()
{
    this->m_routeStackIndex = 0;
    unschedule(schedule_selector(EnemySprite::moveAccordingToRouteStack));
    
    // 再度巡回する
    this->startPatrol();
}


/**
    経路に従って移動する
 */
void EnemySprite::moveAccordingToRouteStack(float frame)
{
    if (this->m_routeStack->empty() || this->m_routeStack->size() <= this->m_routeStackIndex) {
        this->stopMoveAccordingToRouteStack();
        return;
    }
    
    Vec2 nextPos = this->m_routeStack->at(this->m_routeStackIndex);
    this->facingNextPos(nextPos);
    
    if (this->checkFindPlayer()) {
        this->stopMoveAccordingToRouteStack();
        StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
        mainScene->enemyFindPlayer();
        return;
    }
    
    this->moveWorld(this->m_moveSpeed, nextPos);
    this->m_routeStackIndex++;
}


/**
    プレイヤーの追跡を開始する
 */
void EnemySprite::startChasePlayer()
{
    // 巡回は中断する
    this->stopPatrol();
    
    schedule(schedule_selector(EnemySprite::chasePlayer), 0.5f);
}


/**
    プレイヤーの追跡を中止する
 */
void EnemySprite::stopChasePlayer()
{
    unschedule(schedule_selector(EnemySprite::chasePlayer));
    
    // 再度巡回する
    this->startPatrol();
}


/**
    プレイヤーを最短経路で追跡し続ける
 */
void EnemySprite::chasePlayer(float frame)
{
    // プレイヤーへの最短経路を計算
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    CharacterSprite* player = mainScene->m_player;
    std::vector<Vec2> routeStack;
    std::vector<Vec2> shortestRouteStack;
    this->searchShortestRoute(routeStack, shortestRouteStack, this->worldPosition(), player->worldPosition());
    
    // 目の前まで来たらストップ
    if (shortestRouteStack.size() < 3) {
        this->stopChasePlayer();
        return;
    }
    
    // 最短経路でプレイヤーに近づく
    Vec2 nextPos = shortestRouteStack.at(1);
    this->facingNextPos(nextPos);
    this->moveWorld(this->m_moveSpeed, nextPos);
}
