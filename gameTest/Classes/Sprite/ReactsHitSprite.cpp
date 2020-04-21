//
//  ReactsHitSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/20.
//

#include "ReactsHitSprite.hpp"

#pragma mark -
#pragma mark Init
/**
    Sprite::createメソッドをオーバーライド
 
    @param filename 画像リソース名
    @param pos ワールド座標初期位置
    @param direction 向き
    @param hitAction 弾丸に当たった際に実行する処理
    @return Sprite
 */
ReactsHitSprite* ReactsHitSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, std::function<void()> hitAction)
{
    ReactsHitSprite *sprite =  new (std::nothrow) ReactsHitSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, hitAction)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    初期化処理
 
    @param filename 画像リソース名
    @param pos ワールド座標初期位置
    @param direction 向き
    @param hitAction 弾丸に当たった際に実行する処理
 */
bool ReactsHitSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, std::function<void()> hitAction)
{
    if (!GameSpriteBase::initWithFileName(filename, pos, direction)) {
        return false;
    }
    this->m_hitAction = hitAction;
    return true;
}


#pragma mark -
#pragma mark Event
/**
    被弾処理
 
    @param damage ダメージ
    @param bulletDirection 弾の方向
 */
void ReactsHitSprite::hitToBullet(int damage, ::directcion bulletDirection)
{
    // コールバックを実行する
    this->m_hitAction();
}
