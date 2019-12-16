//
//  BulletSprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/10.
//

#include "BulletSprite.hpp"
#include "MainGameScene.hpp"

#pragma mark -
#pragma mark init
/**
    Sprite::createメソッドをオーバーライド
 
    @param filename 弾の画像リソース名
    @param pos 弾のワールド座標初期位置
    @param direction 弾の向き
    @param moveSpeed 弾の移動速度
    @return 弾のSprite
 */
BulletSprite* BulletSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float speed)
{
    BulletSprite *sprite =  new (std::nothrow) BulletSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, speed)) {
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
    @param moveSpeed 弾の移動速度
 */
bool BulletSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float speed)
{
    if (!GameSpriteBase::initWithFileName(filename, pos, direction)) {
        return false;
    }
    this->m_speed = speed;
    return true;
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
    EnemySprite* hitEnemy = this->validateHitEnemy();
    if (hitEnemy != nullptr) {
        MainGameScene *mainScene = (MainGameScene*)this->getParent();
        mainScene->hitEnemy(hitEnemy);
    }
    
    if (!this->canMovePos(this->worldPosition())) {
        unschedule(schedule_selector(BulletSprite::updatePosition));
        this->removeFromParent();
        return;
    }
    
    this->moveWorld(0.1f, this->nextTilePosition());
}


/**
 */
EnemySprite* BulletSprite::validateHitEnemy()
{
    MainGameScene* mainScene = (MainGameScene*)this->getParent();
    Vector<EnemySprite*> enemysVector = mainScene->enemysVector();
    for (int i = 0; i < enemysVector.size(); i++) {
        if (enemysVector.at(i)->worldPosition() != this->worldPosition()) {
            continue;
        }
        
        if (enemysVector.at(i)->directcion() == this->directcion()) {
            return enemysVector.at(i);
        }
    }
    return nullptr;
}

