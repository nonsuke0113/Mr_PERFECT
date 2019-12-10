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
    CharacterSprite *sprite = (CharacterSprite *)GameSpriteBase::create(filename, pos, map);
    if (sprite) {
        sprite->m_moveSpeed = moveSpeed;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    次のタイルに移動する
 */
void CharacterSprite::moveNextTile() {
    Vec2 nextTilePosition = this->nextTilePosition();
    if (nextTilePosition != Vec2 { -1.0f, -1.0f }) {
        this->moveWorld(this->m_moveSpeed, this->nextTilePosition());
    }
}


/**
    キャラクターが向いている方向にいる別のキャラクターを返す
 
    @return CharacterSprite 隣にいる別のキャラクター
 */
CharacterSprite* CharacterSprite::nextCharacter()
{
    Vec2 nextTilePosition = this->nextTilePosition();
    if (nextTilePosition == Vec2 { -1.0f, -1.0f }) {
        return nullptr;
    }
    
    MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
    Vector<CharacterSprite*>* charactersVector = mainScene->charactersVector;
    for (int i = 0; i < charactersVector->size(); i++) {
        if(nextTilePosition == charactersVector->at(i)->worldPosition()) {
            return charactersVector->at(i);
        }
    }
    return nullptr;
}

