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

#include "Const.hpp"

// キャラクターの向き
typedef enum {
    character_back,
    character_right,
    character_front,
    character_left
} characterDirectcion;


class CharacterSprite : public Sprite
{
protected:
    Vec2 m_worldPosition; // ワールド座標
    TMXTiledMap* m_map; // キャラクターが配置されているマップ
    ::characterDirectcion m_characterDirectcion; // キャラクターの向き
    float m_moveSpeed; // 移動速度
    
public:
    static CharacterSprite* create(const std::string& filename, const Vec2 &pos, TMXTiledMap* map, float moveSpeed);
    
    Vec2& worldPosition();
    characterDirectcion characterDirectcion();
    
    void setCharacterDirectcion(::characterDirectcion direction);
    
    void moveWorld(float duration, const Vec2& newPosition);
    void moveNextTile();
    Vec2 nextTilePosition();
    CharacterSprite* nextCharacter();
    int nextTileGID();
};

#endif /* CharacterSprite_hpp */
