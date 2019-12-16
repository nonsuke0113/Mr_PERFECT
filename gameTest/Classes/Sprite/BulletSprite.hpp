//
//  BulletSprite.hpp
//  gameTest-mobile
//
//  弾クラス
//
//  Created by 丹野健介 on 2019/12/10.
//

#ifndef BulletSprite_hpp
#define BulletSprite_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "GameSpriteBase.hpp"
#include "EnemySprite.hpp"


class BulletSprite : public GameSpriteBase
{
protected:
    float m_speed; // 弾の速度
    
    void updatePosition(float frame);
    EnemySprite* validateHitEnemy();
    
public:
    
    static BulletSprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float speed);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float speed);
    
    void shootBullet(::directcion direction);
};


#endif /* BulletSprite_hpp */
