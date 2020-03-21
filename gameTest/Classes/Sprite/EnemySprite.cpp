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
#include "AStarUtils.hpp"

#pragma mark -
#pragma mark Init
/**
    CharacterSprite::createメソッドをオーバーライド
 
    @param filename 敵キャラクターの画像リソース名
    @param pos 敵キャラクターのワールド座標初期位置
    @param direction 敵キャラクターの向き
    @param moveSpeed 敵キャラクターの移動速度
    @param patorolType 敵キャラクターの巡回タイプ
    @return 敵キャラクターのSprite
 */
EnemySprite* EnemySprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float moveSpeed, ::patorolType patorolType)
{
    EnemySprite *sprite =  new (std::nothrow) EnemySprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, moveSpeed, patorolType)) {
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
    @param patorolType 敵キャラクターの巡回タイプ
 */
bool EnemySprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed, ::patorolType patorolType)
{
    if (!CharacterSprite::initWithFileName(filename, pos, direction, moveSpeed)) {
        return false;
    }
    this->m_initPosition = pos;
    this->m_patorolType = patorolType;
    this->m_rotateDirectcion = ::turn_right;
    this->m_hp = 5;
    this->m_routeStack = std::vector<Vec2>();
    this->m_routeStackIndex = 0;
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
    被弾処理
 
    @param damage ダメージ
    @param bulletDirection 弾の方向
 */
void EnemySprite::hitToBullet(int damage, ::directcion bulletDirection)
{
    if (this->directcion() == bulletDirection) {
        this->setHp(0);
    } else {
        this->setHp(this->m_hp - damage);
    }
}


/**
    吹き出しを表示する
 */
void EnemySprite::showSpeechBubble(const std::string& filename)
{
    GameSpriteBase *exclamation = GameSpriteBase::create(filename, Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f }, this->directcion());
    exclamation->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->getParent()->addChild(exclamation);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(0.3f, exclamation->getPosition()));
    actionAry.pushBack(RemoveSelf::create());
    Sequence *actions { Sequence::create(actionAry) };
    exclamation->runAction(actions);
}


/**
    死亡処理
 */
void EnemySprite::dead()
{
    this->removeFromParent();
}


#pragma mark -
/**
    巡回をスケジュール
 */
void EnemySprite::startPatrol() {
    // 巡回をスケジュール
    schedule(schedule_selector(EnemySprite::patrol), 1.0f);
}


/**
    巡回を中止
 */
void EnemySprite::stopPatrol() {
    // 巡回を中止
    unschedule(schedule_selector(EnemySprite::patrol));
}


/**
    巡回する
    移動できないようになるまで、向いている方向でまっすぐ進む
    移動できなくなったら、設定された方向に回転する
 */
void EnemySprite::patrol(float frame) {
    
    if (this->checkFindPlayer()) {
        this->stopPatrol();
        this->startShoot();
        this->startChasePlayer();
        
        // シーンに通知
        StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
        mainScene->enemyFoundPlayer();
        return;
    }
    
    if (this->nextTileGID() == 0) {
        this->moveNextTile();
    } else {
        switch (this->m_patorolType) {
            case ::patorol_lookback:
                this->lookBack();
                break;
            case ::patorol_rotate:
                this->rotate();
                break;
            default:
                break;
        }
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
    反対方向を向く
 */
void EnemySprite::lookBack()
{
    switch (this->m_directcion) {
        case ::front:
            this->setDirectcion(::back);
            break;
        case ::right:
            this->setDirectcion(::left);
            break;
        case ::back:
            this->setDirectcion(::front);
            break;
        case ::left:
            this->setDirectcion(::right);
            break;
        default:
            break;
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
    
    switch (this->m_directcion) {
        case ::front:
            for (int i = 1; this->m_worldPosition.y + i < MAP_TILE_HEGHT; i++) {
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + i };
                if (!this->canMovePos(checkTilePosition)) {
                    return false;
                }
                if (player->worldPosition() == checkTilePosition) {
                    return true;
                }
            }
            break;
        case ::right:
            for (int i = 1; this->m_worldPosition.x + i < MAP_TILE_WIDTH; i++) {
                checkTilePosition = Vec2 { this->m_worldPosition.x + i, this->m_worldPosition.y };
                if (!this->canMovePos(checkTilePosition)) {
                    return false;
                }
                if (player->worldPosition() == checkTilePosition) {
                    return true;
                }
            }
            break;
        case ::back:
            for (int i = 1; this->m_worldPosition.y - i > 0; i++) {
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - i };
                if (!this->canMovePos(checkTilePosition)) {
                    return false;
                }
                if (player->worldPosition() == checkTilePosition) {
                    return true;
                }
            }
            break;
        case ::left:
            for (int i = 1; this->m_worldPosition.x - i > 0; i++) {
                checkTilePosition = Vec2 { this->m_worldPosition.x - i, this->m_worldPosition.y };
                if (!this->canMovePos(checkTilePosition)) {
                    return false;
                }
                if (player->worldPosition() == checkTilePosition) {
                    return true;
                }
            }
            break;
        default:
            break;
    }
    
    return false;
}


/**
    与えられた座標まで、最短経路で移動する
 
    @param pos 移動する座標
 */
void EnemySprite::moveToPos(const Vec2 &pos)
{
    if (!this->m_routeStack.empty()) {
        this->stopMoveAccordingToRouteStack();
    }
    
    // 指定された座標まで最短経路で移動する
    std::vector<Vec2> routeStack = AStarUtils::shortestRouteStack(this, this->worldPosition(), pos);
    this->startMoveAccordingToRouteStack(routeStack);
}


/**
    与えられた経路で移動を開始する
 
    @param routeStack 移動経路
 */
void EnemySprite::startMoveAccordingToRouteStack(const std::vector<Vec2>& routeStack)
{
    // 巡回は中断する
    this->stopPatrol();
    
    std::copy(routeStack.begin(), routeStack.end(), std::back_inserter(this->m_routeStack));
    this->m_routeStackIndex = 0;
    schedule(schedule_selector(EnemySprite::moveAccordingToRouteStack), 0.5f);
}


/**
    経路に従う移動を停止する
 */
void EnemySprite::stopMoveAccordingToRouteStack()
{
    if (!this->m_routeStack.empty()) {
        this->m_routeStack.clear();
    }
    this->m_routeStackIndex = 0;
    unschedule(schedule_selector(EnemySprite::moveAccordingToRouteStack));
}


/**
    経路に従って移動する
 */
void EnemySprite::moveAccordingToRouteStack(float frame)
{
    if (this->m_routeStack.empty() || this->m_routeStack.size() <= this->m_routeStackIndex) {
        this->showSpeechBubble("question.png");
        this->stopMoveAccordingToRouteStack();
        this->startPatrol();
        return;
    }
    
    Vec2 nextPos = this->m_routeStack.at(this->m_routeStackIndex);
    this->facingNextPos(nextPos);
    
    if (this->checkFindPlayer()) {
        this->stopMoveAccordingToRouteStack();
        this->startShoot();
        this->startChasePlayer();
        
        // シーンに通知
        StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
        mainScene->enemyFoundPlayer();
        return;
    }
    
    this->moveWorld(this->m_moveSpeed, nextPos);
    this->m_routeStackIndex++;
}


#pragma mark -
#pragma mark Chase
/**
    プレイヤーの追跡を開始する
 */
void EnemySprite::startChasePlayer()
{
    // 巡回は中断する
    this->stopPatrol();
    
    // 保持しているプレイヤーの座標情報リセット
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    CharacterSprite* player = mainScene->m_player;
    this->m_playerLostPoint = player->worldPosition();
    this->m_playerLostNextPoint = Vec2(-1, -1);
    
    schedule(schedule_selector(EnemySprite::chasePlayer), 0.5f);
}


/**
    プレイヤーの追跡を中止する
 */
void EnemySprite::stopChasePlayer()
{
    unschedule(schedule_selector(EnemySprite::chasePlayer));
}


/**
    プレイヤーを追跡し続ける
 */
void EnemySprite::chasePlayer(float frame)
{
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    CharacterSprite* player = mainScene->m_player;
    
    if (this->checkFindPlayer()) {
        // プレイヤーを最後に見つけた位置を保持
        this->m_playerLostPoint = player->worldPosition();
    }
    else {
        // 見失った地点から、プレイヤーが次に進んだ地点を保持
        if (this->m_playerLostNextPoint == Vec2(-1, -1)) {
            this->m_playerLostNextPoint = player->worldPosition();
            this->stopShoot();
        }
        // 見失った地点まで移動した
        if (this->worldPosition() == this->m_playerLostPoint) {
            this->stopChasePlayer();
            this->loseSightOfPlayer();
        }
    }
    
    // まっすぐプレイヤーに近づく
    if (this->nextCharacter() != player) {
        this->moveNextTile();
    }
}


/**
    プレイヤーを見失った際の処理
 */
void EnemySprite::loseSightOfPlayer()
{
    // プレイヤーが逃げた方を向く
    bool isMoveUpdown = this->worldPosition().x == this->m_playerLostNextPoint.x;
    if (isMoveUpdown) {
        if (this->worldPosition().y > this->m_playerLostNextPoint.y) {
            this->setDirectcion(back);
        } else {
            this->setDirectcion(front);
        }
    } else {
        if (this->worldPosition().x > this->m_playerLostNextPoint.x) {
            this->setDirectcion(left);
        } else {
            this->setDirectcion(right);
        }
    }
    
    // プレイヤーがいれば再度追跡する
    if (this->checkFindPlayer()) {
        this->startShoot();
        this->startChasePlayer();
        
        // シーンに通知
        StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
        mainScene->enemyFoundPlayer();
    }
    // 完全に見失った
    else {
        this->showSpeechBubble("question.png");
        // 初期座標まで最短経路で戻る
        this->moveToPos(this->m_initPosition);
    }
}


#pragma mark -
#pragma mark Shoot
/**
    銃撃を開始する
 */
void EnemySprite::startShoot()
{
    schedule(schedule_selector(EnemySprite::shoot), 0.5f);
}


/**
    銃撃を中止する
 */
void EnemySprite::stopShoot()
{
    unschedule(schedule_selector(EnemySprite::shoot));
}


/**
    銃撃し続ける
 */
void EnemySprite::shoot(float frame)
{
    this->shootBullet();
}
