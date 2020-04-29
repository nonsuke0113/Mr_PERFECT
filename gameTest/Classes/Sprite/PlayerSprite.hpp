//
//  PlayerSprite.hpp
//  gameTest-mobile
//
//  操作キャラクターのクラス
//
//  Created by 丹野健介 on 2020/01/29.
//

#ifndef PlayerSprite_hpp
#define PlayerSprite_hpp

#include "CharacterSprite.hpp"
#include <vector>

class PlayerSprite : public CharacterSprite
{
protected:
    /// 最後に弾丸を打った時間
    float m_timeOfLastShoot;
    
    void setupAnimationCache();
    void dead();
    
public:
    static PlayerSprite* create(const std::string& filename, const Vec2& pos, ::directcion direction, float updatePosFrame);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float updatePosFrame);
    float timeOfLastShoot();
    void setTimeOfLastShoot(float time);
    void setDirectcion(::directcion direction);
    void hitToBullet(int damage, ::directcion bulletDirection);
    void knockWall();
    bool canMoveNextPos();
};

#endif /* PlayerSprite_hpp */
