//
//  PlayerSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/01/29.
//

#include "PlayerSprite.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark Init
/**
    CharacterSprite::createメソッドをオーバーライド
 
    @param filename 操作キャラクターの画像リソース名
    @param pos 操作キャラクターのワールド座標初期位置
    @param direction 操作キャラクターの向き
    @param updatePosFrame 操作キャラクターの座標更新のフレーム
    @return 操作キャラクターのSprite
 */
PlayerSprite* PlayerSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float updatePosFrame)
{
    PlayerSprite *sprite =  new (std::nothrow) PlayerSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, updatePosFrame)) {
        sprite->autorelease();
        return sprite;
    }
    return nullptr;
}


/**
    アニメーションキャッシュに移動用のアニメーションを設定する
 */
void PlayerSprite::setupAnimationCache()
{
    Rect rect = Rect(0, 0, PER_TILE_SIZE, PER_TILE_SIZE);
    
    Animation *animationPlayerFront = Animation::create();
    animationPlayerFront->addSpriteFrame(SpriteFrame::create("player_front1.png", rect));
    animationPlayerFront->addSpriteFrame(SpriteFrame::create("player_front2.png", rect));
    animationPlayerFront->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerFront, "PLAYER_FRONT");
    
    Animation *animationPlayerRight = Animation::create();
    animationPlayerRight->addSpriteFrame(SpriteFrame::create("player_right1.png", rect));
    animationPlayerRight->addSpriteFrame(SpriteFrame::create("player_right2.png", rect));
    animationPlayerRight->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerRight, "PLAYER_RIGHT");
    
    Animation *animationPlayerBack = Animation::create();
    animationPlayerBack->addSpriteFrame(SpriteFrame::create("player_back1.png", rect));
    animationPlayerBack->addSpriteFrame(SpriteFrame::create("player_back2.png", rect));
    animationPlayerBack->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerBack, "PLAYER_BACK");
    
    Animation *animationPlayerLeft = Animation::create();
    animationPlayerLeft->addSpriteFrame(SpriteFrame::create("player_left1.png", rect));
    animationPlayerLeft->addSpriteFrame(SpriteFrame::create("player_left2.png", rect));
    animationPlayerLeft->setDelayPerUnit(CHARACTER_ANIMATION_SPEED);
    AnimationCache::getInstance()->addAnimation(animationPlayerLeft, "PLAYER_LEFT");
}


#pragma mark -
#pragma mark Setter
/**
    向きセッター
 */
void PlayerSprite::setDirectcion(::directcion direction) {
    
    // 変化なしなら何もしない
    if (this->m_directcion == direction) {
        return;
    }
    
    this->m_directcion = direction;
    
    Animation *animation = nullptr;
    switch (direction) {
        case front:
            animation = AnimationCache::getInstance()->getAnimation("PLAYER_FRONT");
            break;
        case right:
            animation = AnimationCache::getInstance()->getAnimation("PLAYER_RIGHT");
            break;
        case back:
            animation = AnimationCache::getInstance()->getAnimation("PLAYER_BACK");
            break;
        case left:
            animation = AnimationCache::getInstance()->getAnimation("PLAYER_LEFT");
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
void PlayerSprite::hitToBullet(int damage, ::directcion bulletDirection)
{
    this->setHp(this->m_hp - damage);
    
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    mainScene->heartOff(this->m_hp);
}


/**
    壁を叩いた処理
 */
void PlayerSprite::knockWall()
{
    GameSpriteBase *knock = nullptr;
    switch (this->directcion()) {
        case ::front:
            knock = GameSpriteBase::create("knock_under.png", this->nextTilePosition(), this->directcion());
            break;
        case ::right:
            knock = GameSpriteBase::create("knock_right.png", this->nextTilePosition(), this->directcion());
            break;
        case ::back:
            knock = GameSpriteBase::create("knock_up.png", this->nextTilePosition(), this->directcion());
            break;
        case ::left:
            knock = GameSpriteBase::create("knock_left.png", this->nextTilePosition(), this->directcion());
            break;
        default:
            break;
    }
    knock->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->getParent()->addChild(knock);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(0.3f, knock->getPosition()));
    actionAry.pushBack(RemoveSelf::create());
    Sequence *actions { Sequence::create(actionAry) };
    knock->runAction(actions);
}


/**
    次の座標に移動可能かどうかを返す
 
    @return 次の座標に移動可能かどうか
 */
bool PlayerSprite::canMoveNextPos()
{
    // 通れない道
    if (!isCanEnterTileGID(this->nextTileGID())) {
        return false;
    }
    
    // 別のゲームスプライトがある
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    for (GameSpriteBase *sprite : mainScene->gameSpriteVector()) {
        if (this->nextTilePosition() == sprite->worldPosition()) {
            return false;
        }
    }
    
    return true;
}


/**
    死亡処理
 */
void PlayerSprite::dead()
{
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    mainScene->missionFailed();
}
