//
//  GameSpriteBase.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/10.
//

#include "GameSpriteBase.hpp"
#include "MainGameScene.hpp"

#pragma mark -
#pragma mark init
/**
    Sprite::createメソッドをオーバーライド
 
    @param filename 画像リソース名
    @param pos ワールド座標初期位置
    @param direction 画像の向き
    @return Sprite
 */
GameSpriteBase* GameSpriteBase::create(const std::string& filename, const Vec2& pos, ::directcion direction)
{
    GameSpriteBase *sprite = new (std::nothrow) GameSpriteBase();
    if (sprite && sprite->initWithFileName(filename, pos, direction))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


/**
    初期化処理
 
    @param filename 画像リソース名
    @param pos ワールド座標初期位置
    @param direction 画像の向き
 */
bool GameSpriteBase::initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    this->m_worldPosition = pos;
    this->setPosition(Vec2(pos.x * PER_TILE_SIZE, (MAP_TILE_HEGHT - pos.y - 1) * PER_TILE_SIZE));
    this->m_directcion = direction;
    return true;
}


#pragma mark -
#pragma mark Getter
/**
    ワールド座標ゲッター
 
    @return スプライトのワールド座標
 */
Vec2& GameSpriteBase::worldPosition() {
    return this->m_worldPosition;
}


/**
    向きゲッター
 
    @param スプライトの向き
 */
directcion GameSpriteBase::directcion() {
    return this->m_directcion;
}


#pragma mark -
#pragma mark Setter
/**
    ワールド座標セッター
 */
void GameSpriteBase::setWorldPosition(Vec2& worldPos) {
    this->m_worldPosition = worldPos;
}


/**
    向きセッター
 */
void GameSpriteBase::setDirectcion(::directcion direction) {
    this->m_directcion = direction;
}


#pragma mark -
#pragma mark Position
/**
    指定された秒数をかけて、新しいワールド座標に移動する
 
    @param duration 移動時間
    @param newPosition 移動する座標(ワールド座標)
 */
void GameSpriteBase::moveWorld(float duration, const Vec2& newPosition) {
    this->m_worldPosition = newPosition;
    MoveTo* actionMove = MoveTo::create(duration, Vec2(newPosition.x * PER_TILE_SIZE,  (MAP_TILE_HEGHT - newPosition.y - 1) * PER_TILE_SIZE));
    this->stopAllActions();
    this->runAction(actionMove);
}


/**
    スプライトが向いている方向の次のタイルのワールド座標を返す
    端にいた場合、-1,-1で返す
 
    @return Vec2 スプライトが向いている方向の次のタイルのワールド座標
 */
Vec2 GameSpriteBase::nextTilePosition()  {
    
    Vec2 nextTilePosition = Vec2 { -1, -1 };
    
    if (this->m_directcion == back && this->m_worldPosition.y != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f };
    }
    else if(this->m_directcion == right && this->m_worldPosition.x + 1.0f != MAP_TILE_WIDTH) {
        nextTilePosition = Vec2 { this->m_worldPosition.x + 1.0f, this->m_worldPosition.y };
    }
    else if (this->m_directcion == front && this->m_worldPosition.y + 1.0f != MAP_TILE_HEGHT) {
        nextTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + 1.0f };
    }
    else if (this->m_directcion == left && this->m_worldPosition.x != 0.0f) {
        nextTilePosition = Vec2 { this->m_worldPosition.x - 1.0f, this->m_worldPosition.y };
    }
    
    return nextTilePosition;
}


/**
    与えられた座標が移動可能かどうか
 
    @param pos 対象の座標
    @return 移動可能かどうか
 */
bool GameSpriteBase::canMovePos(Vec2& pos)
{
    MainGameScene* scene = (MainGameScene*)this->getParent();
    TMXLayer* layer = scene->m_map->getLayer("MAP");
    if (pos.x < 0.0f || pos.x >= MAP_TILE_WIDTH ||
        pos.y < 0.0f || pos.y >= MAP_TILE_HEGHT ||
        layer->getTileGIDAt(pos) - 1.0f != 0) {
        return false;
    }
    return true;
}


/**
    与えられた隣の座標の方向に向きを変える
 
    @param pos 隣の座標
 */
void GameSpriteBase::facingNextPos(Vec2& pos)
{
    if (this->worldPosition().x == pos.x && this->worldPosition().y - 1 == pos.y) {
        this->setDirectcion(back);
    }
    else if (this->worldPosition().x + 1 == pos.x && this->worldPosition().y == pos.y) {
        this->setDirectcion(right);
    }
    else if (this->worldPosition().x == pos.x && this->worldPosition().y + 1 == pos.y) {
        this->setDirectcion(front);
    }
    else if (this->worldPosition().x - 1== pos.x && this->worldPosition().y == pos.y) {
        this->setDirectcion(left);
    }
}


/**
    スプライトが向いている方向の次のタイルのIDを返す
 
    @return int 次のタイルのID
 */
int GameSpriteBase::nextTileGID()  {
    
    int tileGID = -1;
    Vec2 nextTilePosition = this->nextTilePosition();
    
    if(nextTilePosition != Vec2 { -1.0f, -1.0f }) {
        MainGameScene* scene = (MainGameScene*)this->getParent();
        TMXLayer* layer = scene->m_map->getLayer("MAP");
        tileGID = layer->getTileGIDAt(nextTilePosition) - 1;
    }
    
    return tileGID;
}
