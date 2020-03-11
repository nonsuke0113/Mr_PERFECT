//
//  BulletSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/10.
//

#include "BulletSprite.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark Init
/**
    Sprite::createメソッドをオーバーライド
 
    @param pos 弾のワールド座標初期位置
    @param direction 弾の向き
    @param charactor 発砲したキャラクター
    @param moveSpeed 弾の移動速度
    @return 弾のSprite
 */
BulletSprite* BulletSprite::create(const Vec2& pos, ::directcion direction, CharacterSprite* charactor, float speed)
{
    // 向きに応じてファイル名を設定
    std::string filename;
    switch (direction) {
        case front:
            filename = "bullet_front.png";
            break;
        case right:
            filename = "bullet_right.png";
            break;
        case back:
            filename = "bullet_back.png";
            break;
        case left:
            filename = "bullet_left.png";
            break;
        default:
            break;
    }
    
    BulletSprite *sprite =  new (std::nothrow) BulletSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, charactor, speed)) {
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    初期化処理
 
    @param filename 弾の画像リソース名
    @param pos 弾のワールド座標初期位置
    @param direction 画像の向き
    @param charactor 発砲したキャラクター
    @param moveSpeed 弾の移動速度
 */
bool BulletSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, CharacterSprite* charactor, float speed)
{
    if (!GameSpriteBase::initWithFileName(filename, pos, direction)) {
        return false;
    }
    this->m_shootCharactor = charactor;
    this->m_power = 1;
    this->m_speed = speed;
    return true;
}


#pragma mark -
#pragma mark Getter
/**
    威力ゲッター
 
    @return 弾の威力
 */
int BulletSprite::power() {
    return this->m_power;
}


#pragma mark -
/**
    弾が撃たれた際に呼び出される関数
 
    @param direction 弾の発射された方向
 */
void BulletSprite::shootBullet(::directcion direction)
{
    this->setDirectcion(direction);
    schedule(schedule_selector(BulletSprite::updatePosition), this->m_speed);
}


/**
    弾の座標更新
    進めなくなるまで真っ直ぐ進む
 */
void BulletSprite::updatePosition(float frame)
{
    CharacterSprite* hitCharacter = this->validateHit();
    // 被弾処理
    if (hitCharacter != nullptr) {
        hitCharacter->hitToBullet(this->power(), this->directcion());
    }
    // 被弾した or 進めなくなったら自身を削除する
    if (hitCharacter != nullptr || !this->canMovePos(this->worldPosition())) {
        unschedule(schedule_selector(BulletSprite::updatePosition));
        this->removeFromParentAndCleanup(true);
        this->m_shootCharactor->m_bullet = nullptr;
        return;
    }
    
    this->moveWorld(0.1f, this->nextTilePosition());
}


/**
    弾がキャラクターに当たったかどうかを検証する
    当たっているキャラクターがいなかった場合、nullptrを返す
 
    @return 弾に当たったキャラクター or nullptr
 */
CharacterSprite* BulletSprite::validateHit()
{
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    Vector<CharacterSprite*> charactersVector = mainScene->charactersVector();
    for (int i = 0; i < charactersVector.size(); i++) {
        if (charactersVector.at(i)->worldPosition() == this->worldPosition() &&
            charactersVector.at(i) != this->m_shootCharactor) {
            return charactersVector.at(i);
        }
    }
    return nullptr;
}

