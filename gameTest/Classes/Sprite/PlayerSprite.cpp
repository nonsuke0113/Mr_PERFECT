//
//  PlayerSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/01/29.
//

#include "PlayerSprite.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark init
/**
    CharacterSprite::createメソッドをオーバーライド
 
    @param filename 操作キャラクターの画像リソース名
    @param pos 操作キャラクターのワールド座標初期位置
    @param direction 操作キャラクターの向き
    @param moveSpeed 操作キャラクターの移動速度
    @return 操作キャラクターのSprite
 */
PlayerSprite* PlayerSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float moveSpeed)
{
    PlayerSprite *sprite =  new (std::nothrow) PlayerSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, moveSpeed)) {
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
    死亡処理
 */
void PlayerSprite::dead()
{
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    mainScene->missionFailed();
}
