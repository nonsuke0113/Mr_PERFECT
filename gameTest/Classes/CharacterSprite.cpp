//
//  CharacterSprite.cpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#include "MainGameScene.hpp"
#include "CharacterSprite.hpp"

/**
    Sprite::createメソッドをオーバーライド
 
    @param filename キャラクターの画像リソース名
    @param pos キャラクターのワールド座標初期位置
    @param map キャラクターが配置されているマップ
    @param moveSpeed キャラクターの移動速度
    @return キャラクターのSprite
 */
CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2& pos, TMXTiledMap* map, float moveSpeed)
{
    CharacterSprite *sprite = new (std::nothrow) CharacterSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->m_worldPosition = pos;
        sprite->setPosition(Vec2(pos.x * PER_TILE_SIZE, (MAP_TILE_HEGHT - pos.y - 1) * PER_TILE_SIZE));
        sprite->m_map = map;
        sprite->m_characterDirectcion = character_front;
        sprite->m_moveSpeed = moveSpeed;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


#pragma mark -
#pragma mark Getter
/**
    ワールド座標ゲッター
 
    @return キャラクターのワールド座標
 */
Vec2& CharacterSprite::worldPosition() {
    return this->m_worldPosition;
}


/**
    キャラクターの向きゲッター
 
    @param キャラクターの向き
 */
characterDirectcion CharacterSprite::characterDirectcion() {
    return this->m_characterDirectcion;
}


#pragma mark -
#pragma mark Setter
/**
    キャラクターの向きをセットする
    @return
 */
void CharacterSprite::setCharacterDirectcion(::characterDirectcion direction) {
    this->m_characterDirectcion = direction;
}


#pragma mark -
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
    次のタイルに移動する
 */
void CharacterSprite::moveNextTile() {
    this->moveWorld(this->m_moveSpeed, this->nextTilePosition());
}


/**
    キャラクターが向いている方向の次のタイルのワールド座標を返す
 
    @return Vec2 キャラクターが向いている方向の次のタイルのワールド座標
 */
Vec2 CharacterSprite::nextTilePosition()  {
    
    Vec2 nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y };
    
    if(this->m_characterDirectcion == character_back && this->m_worldPosition.y != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f };
    }
    else if(this->m_characterDirectcion == character_right && this->m_worldPosition.x != MAP_TILE_WIDTH - 1.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x + 1.0f, this->m_worldPosition.y };
    }
    else if (this->m_characterDirectcion == character_front && this->m_worldPosition.y != MAP_TILE_HEGHT - 1.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + 1.0f };
    }
    else if (this->m_characterDirectcion == character_left && this->m_worldPosition.x != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x - 1.0f, this->m_worldPosition.y };
    }
    
    return nextTilePosition;
}


/**
    キャラクターが向いている方向の次のタイルのIDを返す
 
    @return int 次のタイルのID
 */
int CharacterSprite::nextTileGID()  {
    
    int tileGID = -1;
    Vec2 nextTilePosition = this->nextTilePosition();
    
    if(nextTilePosition.x != -1.0f && nextTilePosition.x + 1.0f != MAP_TILE_WIDTH &&
       nextTilePosition.y != -1.0f && nextTilePosition.y + 1.0f != MAP_TILE_HEGHT) {
        TMXLayer* layer = this->m_map->getLayer("MAP");
        tileGID = layer->getTileGIDAt(nextTilePosition) - 1;
    }
    
    return tileGID;
}


/**
    キャラクターが向いている方向にいる別のキャラクターを返す
 
    @return CharacterSprite 隣にいる別のキャラクター
 */
CharacterSprite* CharacterSprite::nextCharacter()  {
    Vec2 nextTilePosition = this->nextTilePosition();
    MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
    std::vector<CharacterSprite*> charactersVector = mainScene->charactersVector;
    for (int i = 0; i < charactersVector.size(); i++) {
        if(nextTilePosition == charactersVector[i]->worldPosition()) {
            return charactersVector[i];
        }
    }
    return nullptr;
}
