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
    @param moveSpeed キャラクターの移動速度
    @return キャラクターのSprite
 */
CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2& pos, float moveSpeed)
{
    CharacterSprite *sprite = (CharacterSprite *)GameSpriteBase::create(filename, pos);
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
    if (this->canMovePos(nextTilePosition)) {
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
    
//    MainGameScene* mainScene = (MainGameScene*)this->getParent();
//    Vector<Node*> nodes = mainScene->getChildren();
//    for (int i = 0; i < nodes.size(); i++) {
//        if (<#condition#>) {
//            <#statements#>
//        }
//        
//        
//        if(nextTilePosition == nodes.at(i)->worldPosition()) {
//            return nodes.at(i);
//        }
//    }
    return nullptr;
}

