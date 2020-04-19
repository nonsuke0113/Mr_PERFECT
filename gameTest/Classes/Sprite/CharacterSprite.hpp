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
    
    virtual void setupAnimationCache();
    virtual void dead();
    
public:
    Sprite *m_bullet; // 発砲した弾丸
    /// 座標更新のフレーム
    float m_updatePosFrame;
    
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float updatePosFrame);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float updatePosFrame);
    int hp();
    void setHp(int hp);
    void moveNextTile();
    CharacterSprite* nextCharacter();
    void shootBullet();
    virtual void hitToBullet(int damage, ::directcion bulletDirection);
    
};


#endif /* CharacterSprite_hpp */
