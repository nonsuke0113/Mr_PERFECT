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
    float m_moveSpeed; // 移動速度
    
    virtual void setupAnimationCache();
    
public:
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    
    void moveNextTile();
    CharacterSprite* nextCharacter();
};


#endif /* CharacterSprite_hpp */
