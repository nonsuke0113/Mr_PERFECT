//
//  CharacterSprite.cpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#include "CharacterSprite.hpp"

CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2 &pos, TMXTiledMap* map)
{
    CharacterSprite *sprite = new (std::nothrow) CharacterSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        
        // ワールド座標初期化
        sprite->m_worldPosition = pos;
        sprite->setPosition(Vec2(pos.x * PER_TILE_SIZE, (MAP_TILE_HEGHT - pos.y - 1) * PER_TILE_SIZE));
        
        sprite->m_map = map;
        
        sprite->m_characterDirectcion = character_front;
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

/**
 ワールド座標ゲッター
 */
Vec2& CharacterSprite::worldPosition() {
    return this->m_worldPosition;
}

/**
 */
characterDirectcion CharacterSprite::characterDirectcion() {
    return this->m_characterDirectcion;
}

/**
 */
void CharacterSprite::setCharacterDirectcion(::characterDirectcion direction) {
    this->m_characterDirectcion = direction;
}

/**
 指定された秒数をかけて、新しいワールド座標に移動する
 
 @param duration 移動時間
 @param newPosition 移動する座標(ワールド座標)
 */
void CharacterSprite::moveWorld(float duration, const Vec2& newPosition) {
    this->m_worldPosition = newPosition;
    MoveTo* actionMove = MoveTo::create(duration, Vec2(newPosition.x * PER_TILE_SIZE,  (MAP_TILE_HEGHT - newPosition.y - 1) * PER_TILE_SIZE));
    this->stopAllActions();
    this->runAction(actionMove);
}

/**
 */
Vec2 CharacterSprite::nextTilePosition()  {
    
    Vec2 nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y };
    
    if(this->m_characterDirectcion == character_back && this->m_worldPosition.y != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y-1.0f };
    }
    else if(this->m_characterDirectcion == character_right && this->m_worldPosition.x != MAP_TILE_WIDTH-1.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x+1, this->m_worldPosition.y };
    }
    else if (this->m_characterDirectcion == character_front && this->m_worldPosition.y != MAP_TILE_HEGHT-1.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y+1.0f };
    }
    else if (this->m_characterDirectcion == character_left && this->m_worldPosition.x != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x-1.0f, this->m_worldPosition.y };
    }
    
    return nextTilePosition;
}

/**
 */
int CharacterSprite::getNextTileGID()  {
    
    this->m_map->getParent();
    
    int tileGID = -1;
    Vec2 nextTilePosition = this->nextTilePosition();
    
    if(nextTilePosition.x != -1.0f && nextTilePosition.x != MAP_TILE_WIDTH &&
       nextTilePosition.y != -1.0f && nextTilePosition.y != MAP_TILE_HEGHT) {
        TMXLayer* layer = this->m_map->getLayer("Ground");
        tileGID = layer->getTileGIDAt(nextTilePosition)-1;
    }
    
    return tileGID;
}
