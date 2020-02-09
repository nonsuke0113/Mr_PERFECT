//
//  CharacterSprite.hpp
//  tannoGame-mobile
//
//  キャラクタークラス
//
//  Created by 健介 丹野 on 2018/10/22.
//

#ifndef CharacterSprite_hpp
#define CharacterSprite_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "GameSpriteBase.hpp"

class CharacterSprite : public GameSpriteBase
{
protected:
    int m_hp; // HP
    float m_moveSpeed; // 移動速度
    
    virtual void setupAnimationCache();
    virtual void dead();
    
public:
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    
    int hp();
    void setHp(int hp);
    
    void moveNextTile();
    CharacterSprite* nextCharacter();
    
    void shootBullet();
    virtual void hitToBullet(int damage, ::directcion bulletDirection);
};


#endif /* CharacterSprite_hpp */
