//
//  CharacterSprite.cpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#include "StageSceneBase.hpp"
#include "CharacterSprite.hpp"
#include "BulletSprite.hpp"
#include <AudioEngine.h>

#pragma mark -
#pragma mark Init
/**
    Sprite::createメソッドをオーバーライド
 
    @param filename キャラクターの画像リソース名
    @param pos キャラクターのワールド座標初期位置
    @param direction キャラクターの向き
    @param updatePosFrame キャラクターの座標更新のフレーム
    @return キャラクターのSprite
 */
CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float updatePosFrame)
{
    CharacterSprite *sprite =  new (std::nothrow) CharacterSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, updatePosFrame)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    初期化処理
 
    @param filename キャラクターの画像リソース名
    @param pos キャラクターのワールド座標初期位置
    @param direction キャラクターの向き
    @param updatePosFrame キャラクターの座標更新のフレーム
 */
bool CharacterSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float updatePosFrame)
{
    this->setupAnimationCache();
    if (!ReactsHitSprite::initWithFileName(filename, pos, direction, nullptr)) {
        return false;
    }
    this->m_hp = 3;
    this->m_updatePosFrame = updatePosFrame;
    this->m_bullet = nullptr;
    return true;
}


/**
    アニメーションキャッシュに移動用のアニメーションを設定する
    子クラスにて実装する
 */
void CharacterSprite::setupAnimationCache()
{
    return;
}


#pragma mark -
#pragma mark Getter
/**
    HPゲッター
 
    @return キャラクターのHP
 */
int CharacterSprite::hp() {
    return this->m_hp;
}


#pragma mark -
#pragma mark Setter
/**
    HPセッター
    HPが0以下であれば死亡処理を実行する
 */
void CharacterSprite::setHp(int hp) {
    this->m_hp = hp;
    if (this->m_hp <= 0) {
        this->dead();
    }
}


#pragma mark -
/**
    キャラクターのHPが0以下になった場合の処理
    子クラスにて実装する
 */
void CharacterSprite::dead()
{
    return;
}


/**
    次のタイルに移動する
 */
void CharacterSprite::moveNextTile()
{
    // 移動できなかったら何もしない
    Vec2 nextTilePosition = this->nextTilePosition();
    if (!this->canMovePos(nextTilePosition)) {
        return;
    }
    
    this->moveWorld(this->nextTilePosition());
}


/**
    キャラクターが向いている方向にいる別のキャラクターを返す
 
    @return CharacterSprite 隣にいる別のキャラクター
 */
CharacterSprite* CharacterSprite::nextCharacter()
{
    Vec2 nextTilePosition = this->nextTilePosition();
    if (nextTilePosition == Vec2 { -1.0f, -1.0f }) {
        return nullptr;
    }
    
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    Vector<CharacterSprite*> charactersVector = mainScene->charactersVector();
    for (int i = 0; i < charactersVector.size(); i++) {
        if(nextTilePosition == charactersVector.at(i)->worldPosition()) {
            return charactersVector.at(i);
        }
    }
    return nullptr;
}


/**
    自身の向いている方向に弾を発射する
 */
void CharacterSprite::shootBullet()
{
    if (this->m_bullet != nullptr) {
        return;
    }
    
    // SE再生
    experimental::AudioEngine::play2d("handgun-firing1.mp3", false);
    
    BulletSprite* bullet = BulletSprite::create(this->nextTilePosition(), this->directcion(), this, 0.1f);
    this->m_bullet = bullet;
    bullet->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->getParent()->addChild(bullet);
    bullet->shootBullet(this->directcion());
}


/**
    被弾処理
 
    @param damage ダメージ
    @param bulletDirection 弾の方向
 */
void CharacterSprite::hitToBullet(int damage, ::directcion bulletDirection)
{
    this->setHp(this->m_hp - damage);
}
