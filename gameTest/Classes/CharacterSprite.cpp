//
//  CharacterSprite.cpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#include "CharacterSprite.hpp"
#include "Const.hpp"

CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2 &pos)
{
    CharacterSprite *sprite = new (std::nothrow) CharacterSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        
        sprite->worldPosition = pos;
        sprite->setPosition(Vec2(pos.x * PER_TILE_SIZE, pos.y * PER_TILE_SIZE));
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void CharacterSprite::moveWorld(float duration, const Vec2& newPosition) {
    this->worldPosition = newPosition;
    MoveTo* actionMove = MoveTo::create(duration, Vec2(newPosition.x * PER_TILE_SIZE, newPosition.y * PER_TILE_SIZE));
    this->stopAllActions();
    this->runAction(actionMove);
}
