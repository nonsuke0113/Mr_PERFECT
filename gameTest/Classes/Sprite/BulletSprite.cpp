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
    @param updatePosFrame 弾の移動速度
    @return 弾のSprite
 */
BulletSprite* BulletSprite::create(const Vec2& pos, ::directcion direction, CharacterSprite* charactor, float updatePosFrame)
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
    if (sprite && sprite->initWithFileName(filename, pos, direction, charactor, updatePosFrame)) {
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
    @param updatePosFrame 弾の座標更新のフレーム
 */
bool BulletSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, CharacterSprite* charactor, float updatePosFrame)
{
    if (!GameSpriteBase::initWithFileName(filename, pos, direction)) {
        return false;
    }
    this->m_shootCharactor = charactor;
    this->m_power = 1;
    this->m_updatePosFrame = updatePosFrame;
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
    schedule(schedule_selector(BulletSprite::updatePosition), this->m_updatePosFrame);
}


/**
    弾の座標更新
    進めなくなるまで真っ直ぐ進む
 */
void BulletSprite::updatePosition(float frame)
{
    // 敵キャラクターの撃った弾は敵キャラクターに当たらないようにする
    StageSceneBase *mainScene = (StageSceneBase*)this->getParent();
    ReactsHitSprite *sprite = this->validateHit();
    if ((this->m_shootCharactor != mainScene->m_player) &&
        sprite != mainScene->m_player) {
        sprite = nullptr;
    }
    
    // 被弾処理
    ReactsHitSprite *hitSprite = dynamic_cast<ReactsHitSprite*>(sprite);
    if (hitSprite != nullptr) {
        hitSprite->hitToBullet(this->power(), this->directcion());
    }
    
    // 被弾した or 進めなくなったら自身を削除する
    if (sprite != nullptr ||
        (!this->canMovePos(this->worldPosition()) && this->m_shootCharactor->worldPosition() != this->worldPosition())) {
        unschedule(schedule_selector(BulletSprite::updatePosition));
        this->removeFromParentAndCleanup(true);
        this->m_shootCharactor->m_bullet = nullptr;
        return;
    }
    
    this->moveWorld(this->nextTilePosition());
}


/**
    弾がスプライトに当たったかどうかを検証する
    当たっているスプライトがなかった場合、nullptrを返す
 
    @return 弾に当たったスプライト or nullptr
 */
ReactsHitSprite* BulletSprite::validateHit()
{
    StageSceneBase* mainScene = (StageSceneBase*)this->getParent();
    Vector<GameSpriteBase*> gameSpriteVector = mainScene->gameSpriteVector();
    for (GameSpriteBase* srpite : gameSpriteVector) {
        ReactsHitSprite *hitSprite = dynamic_cast<ReactsHitSprite*>(srpite);
        if (hitSprite != nullptr &&
            hitSprite->worldPosition() == this->worldPosition() &&
            hitSprite != this->m_shootCharactor)
        {
            return hitSprite;
        }
    }
    return nullptr;
}

