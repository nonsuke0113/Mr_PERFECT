//
//  BulletSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/10.
//

#include "BulletSprite.hpp"

/**
    Sprite::createメソッドをオーバーライド
 
    @param filename 弾の画像リソース名
    @param pos 弾のワールド座標初期位置
    @param map 弾が配置されているマップ
    @param moveSpeed 弾の移動速度
    @return 弾のSprite
 */
BulletSprite* BulletSprite::create(const std::string& filename, const Vec2& pos, TMXTiledMap* map, float speed)
{
    BulletSprite *sprite = (BulletSprite *)GameSpriteBase::create(filename, pos, map);
    if (sprite) {
        sprite->m_speed = speed;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    
 */
void BulletSprite::shootBullet(const std::string& filename, const Vec2& pos, TMXTiledMap* map, float speed, ::directcion direction)
{
    BulletSprite* bullet = BulletSprite::create(filename, pos, map, speed);
    bullet->setDirectcion(direction);
}


/**
 */
void BulletSprite::updatePosition(float frame)
{
    Vec2 nextTilePos = this->nextTilePosition();
}
