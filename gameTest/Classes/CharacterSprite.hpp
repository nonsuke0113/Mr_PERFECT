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

#include "Const.hpp"

class CharacterSprite : public Sprite
{
public:
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, TMXTiledMap* map);
    Vec2& worldPosition();
    characterDirectcion characterDirectcion();
    void setCharacterDirectcion(::characterDirectcion direction);
    void moveWorld(float duration, const Vec2& newPosition);
    Vec2 nextTilePosition();
    int getNextTileGID();
private:
    // ワールド座標
    Vec2 m_worldPosition;
    //
    TMXTiledMap* m_map;
    //
    ::characterDirectcion m_characterDirectcion;
};

#endif /* CharacterSprite_hpp */
