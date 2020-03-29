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
    this->m_initPatorolType = patorolType;
    this->m_patorolType = patorolType;
    this->m_rotateDirection = ::turn_none;
    this->m_hp = 5;
    this->m_routeStack = std::vector<Vec2>();
    this->m_routeStackIndex = 0;
    this->m_isFoundPlayer = false;
    this->m_movingHeardSoundPoint = false;
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


/**
    巡回の方向セッター
 */
void EnemySprite::setRotateDirectcion(::rotateDirectcion rotateDirection)
{
    this->m_rotateDirection = rotateDirection;
}


#pragma mark -
#pragma mark Behavior
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
 
    @param speechBubbleType 「！」or「？」
 */
void EnemySprite::showSpeechBubble(::speechBubbleType speechBubbleType)
{
    GameSpriteBase *speechBubble = nullptr;
    switch (speechBubbleType) {
        case ::exclamation:
            speechBubble = GameSpriteBase::create("exclamation.png", Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f }, this->directcion());
            this->m_movingHeardSoundPoint = true;
            break;
        case ::question:
            speechBubble = GameSpriteBase::create("question.png", Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f }, this->directcion());
            break;
        default:
            break;
    }
    speechBubble->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->getParent()->addChild(speechBubble);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(0.3f, speechBubble->getPosition()));
    actionAry.pushBack(RemoveSelf::create());
    Sequence *actions { Sequence::create(actionAry) };
    speechBubble->runAction(actions);
}


/**
    与えられた座標に最短経路で移動する
    
    @param pos 移動する座標
*/
void EnemySprite::moveToPos(Vec2 const& pos)
{
    this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){
        // 経路情報を初期化する
        if (!this->m_routeStack.empty()) {
            this->m_routeStack.clear();
        }
        this->m_routeStackIndex = 0;
        // 最短経路計算
        this->m_routeStack = AStarUtils::shortestRouteStack(this, this->worldPosition(), pos);
        // 移動開始
        this->m_patorolType = ::patorol_according;
        
    }),nullptr));
}


/**
    設定された回転方向に応じて、向いている方向を変える
 */
void EnemySprite::rotate()
{
    switch (this->m_rotateDirection) {
        case ::turn_right:
            this->turnRight();
            break;
        case ::turn_left:
            this->turnLeft();
            break;
        case ::turn_none:
        default:
            break;
    }
}


/**
    死亡処理
 */
void EnemySprite::dead()
{
    this->removeFromParent();
}


#pragma mark -
#pragma mark Update
/**
    定期処理
 */
void EnemySprite::update(float delta)
{
    // 警備中ではない
    if (this->m_patorolType == ::patorol_none) {
        return;
    }
    
    // 警備中に、プレイヤーを発見
    if (this->checkFindPlayer()) {
        this->foundPlayer();
    }
    // プレイヤーを未発見
    else {
        this->losePlayer();
    }
    
    // 警備タイプに応じた処理
    switch (this->m_patorolType) {
        case ::patorol_roundtrip:
            this->patrolRoundTrip();
            break;
        case ::patorol_rotate:
            this->patrolRotate();
            break;
        case ::patorol_chase:
            this->patrolChase();
            break;
        case ::patorol_according:
            this->patrolAccording();
            break;
        default:
            break;
    }
    
}



/**
    プレイヤー発見時の処理
 */
void EnemySprite::foundPlayer()
{
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    
    // プレイヤーを最後に見つけた位置を保持
    this->m_playerLostPoint = mainScene->m_player->worldPosition();
    
    // 警備タイプ更新
    this->m_patorolType = patorol_chase;
    
    // シーンに通知
    if (!this->m_isFoundPlayer) {
        this->m_isFoundPlayer = true;
        mainScene->enemyFoundPlayer();
    }
}


/**
    プレイヤーを見失った際の処理
 */
void EnemySprite::losePlayer()
{
    // 追跡中でなければ何もしない
    if (this->m_patorolType != patorol_chase) {
        return;
    }
    
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    
    if (this->m_isFoundPlayer) {
        this->m_isFoundPlayer = false;
        // 見失った直後のプレイヤー座標を保持
        this->m_playerLostNextPoint = mainScene->m_player->worldPosition();
    }
    
    // 見失った地点まで辿り着いた
    if (this->worldPosition() == this->m_playerLostPoint) {
        // プレイヤーの進んだ方向を向く
        this->facingNextPos(this->m_playerLostNextPoint);
        // 完全に見失った
        if (!this->checkFindPlayer()) {
            this->showSpeechBubble(::question);
            // 初期位置に戻る
            this->moveToPos(this->m_initWorldPosition);
        }
    }
}


#pragma mark -
#pragma mark Patrol
/**
    警備開始
 */
void EnemySprite::startPatrol() {
    // 更新処理開始
    this->scheduleUpdate();
}


/**
    警備中止
 */
void EnemySprite::stopPatrol() {
    // 警備を中止
    this->m_patorolType = ::patorol_none;
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
    警備する
    進めなくなったら折り返す
 */
void EnemySprite::patrolRoundTrip()
{
    // インターバルが経過していなければ何もしない
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    if (fmod(mainScene->m_time, 30) != 0) {
        return;
    }
    
    // 真っ直ぐ進む
    if (this->canMovePos(this->nextTilePosition())) {
        this->moveNextTile();
    }
    // 進めなかったら向きを反転する
    else {
        this->lookback();
    }
}


/**
    警備する
    決まった方向に巡回する
 */
void EnemySprite::patrolRotate()
{
    // インターバルが経過していなければ何もしない
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    if (fmod(mainScene->m_time, 30) != 0) {
        return;
    }
    
    // 回転方向に応じた隣の座標を取得(右or左)
    Vec2 nextRotatePos = Vec2(0.0f, 0.0f);
    switch (this->m_rotateDirection) {
        case ::turn_right:
            nextRotatePos = this->rightTilePosition();
            break;
        case ::turn_left:
            nextRotatePos = this->leftTilePosition();
            break;
        case ::turn_none:
            return;
        default:
            break;
    }
    
    // 回転した隣に進めるなら向きを回転する
    if (this->canMovePos(nextRotatePos)) {
        this->facingNextPos(nextRotatePos);
    }
    // 真っ直ぐ進む
    if (this->canMovePos(this->nextTilePosition())) {
        this->moveNextTile();
    }
    // 進めなかったら向きを回転する
    else {
        this->rotate();
    }
}


/**
    警備する
    プレイヤーを追跡する
 */
void EnemySprite::patrolChase()
{
    // インターバルが経過していなければ何もしない
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    if (fmod(mainScene->m_time, 30) != 0) {
        return;
    }
    
    // 真っ直ぐ進む
    if (this->canMovePos(this->nextTilePosition()) &&
        this->nextCharacter() != mainScene->m_player) {
        this->moveNextTile();
    }
    
    // 弾を撃つ
    if (fmod(mainScene->m_time, 60) == 0) {
        this->shootBullet();
    }
}


/**
    警備する。
    セットされた経路に従って移動する。
 */
void EnemySprite::patrolAccording()
{
    // インターバルが経過していなければ何もしない
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    if (fmod(mainScene->m_time, 30) != 0) {
        return;
    }
    
    // 経路移動完了
    if (this->m_routeStack.size() <= this->m_routeStackIndex) {
        // 音が聞こえた位置まで移動したら、初期位置に戻る
        if (this->m_movingHeardSoundPoint) {
            this->m_movingHeardSoundPoint = false;
            this->showSpeechBubble(::question);
            this->moveToPos(this->m_initWorldPosition);
        }
        // 初期位置に戻ってきた
        else if(this->worldPosition() == this->m_initWorldPosition) {
            this->m_patorolType = this->m_initPatorolType;
            this->setDirectcion(this->m_initDirectcion);
        }
        return;
    }
    
    // 真っ直ぐ進む
    Vec2 nextPos = this->m_routeStack.at(this->m_routeStackIndex);
    this->facingNextPos(nextPos);
    if (this->canMovePos(nextPos) && this->nextCharacter() != mainScene->m_player) {
        this->moveNextTile();
        if (this->worldPosition() == nextPos) {
            this->m_routeStackIndex++;
        }
    }
}

