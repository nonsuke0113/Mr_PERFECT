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
private:
    Vec2 m_worldPosition; // ワールド座標
    TMXTiledMap* m_map; // キャラクターが配置されているマップ
    ::characterDirectcion m_characterDirectcion; // キャラクターの向き
    
public:
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, TMXTiledMap* map);
    Vec2& worldPosition();
    characterDirectcion characterDirectcion();
    void setCharacterDirectcion(::characterDirectcion direction);
    void moveWorld(float duration, const Vec2& newPosition);
    Vec2 nextTilePosition();
    CharacterSprite* getNextCharacter();
    int getNextTileGID();
};

#endif /* CharacterSprite_hpp */
