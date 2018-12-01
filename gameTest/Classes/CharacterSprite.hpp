//
//  CharacterSprite.hpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#ifndef CharacterSprite_hpp
#define CharacterSprite_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CharacterSprite : public Sprite
{
public:
    
    Vec2 worldPosition;
    
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos);
    void moveWorld(float duration, const Vec2& newPosition);
};

#endif /* CharacterSprite_hpp */
