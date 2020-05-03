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
#include "CharacterSprite.hpp"
#include "ReactsHitSprite.hpp"

class BulletSprite : public GameSpriteBase
{
protected:
    /// 撃ったキャラクター
    CharacterSprite* m_shootCharactor;
    /// 威力
    int m_power;
    /// 座標更新のフレーム
    float m_updatePosFrame;
    
    bool canMovePos(Vec2 const& pos);
    void updatePosition(float frame);
    ReactsHitSprite* validateHit();
    
public:
    static BulletSprite* create(const Vec2 &pos, ::directcion direction, CharacterSprite* charactor, float updatePosFrame);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, CharacterSprite* charactor, float updatePosFrame);
    int power();
    void shootBullet(::directcion direction);
    
};


#endif /* BulletSprite_hpp */
