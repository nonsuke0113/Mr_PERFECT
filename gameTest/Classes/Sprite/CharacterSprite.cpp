//
//  CharacterSprite.cpp
//  tannoGame-mobile
//
//  Created by 健介 丹野 on 2018/10/22.
//

#include "MainGameScene.hpp"
#include "CharacterSprite.hpp"

#pragma mark -
#pragma mark init
/**
    Sprite::createメソッドをオーバーライド
 
    @param filename キャラクターの画像リソース名
    @param pos キャラクターのワールド座標初期位置
    @param direction キャラクターの向き
    @param moveSpeed キャラクターの移動速度
    @return キャラクターのSprite
 */
CharacterSprite* CharacterSprite::create(const std::string& filename, const Vec2& pos, ::directcion direction, float moveSpeed)
{
    CharacterSprite *sprite =  new (std::nothrow) CharacterSprite;
    if (sprite && sprite->initWithFileName(filename, pos, direction, moveSpeed)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    初期化処理
 
    @param filename キャラクターの画像リソース名
    @param pos キャラクターのワールド座標初期位置
    @param direction キャラクターの向き
    @param moveSpeed キャラクターの移動速度
 */
bool CharacterSprite::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed)
{
    if (!GameSpriteBase::initWithFileName(filename, pos, direction)) {
        return false;
    }
    this->m_moveSpeed = moveSpeed;
    return true;
}


#pragma mark -
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
    
    MainGameScene* mainScene = (MainGameScene*)this->getParent();
    Vector<CharacterSprite*> charactersVector = mainScene->charactersVector();
    for (int i = 0; i < charactersVector.size(); i++) {
        if(nextTilePosition == charactersVector.at(i)->worldPosition()) {
            return charactersVector.at(i);
        }
    }
    return nullptr;
}

