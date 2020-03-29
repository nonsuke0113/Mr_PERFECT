//
//  GameSpriteBase.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/10.
//

#include "GameSpriteBase.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark Init
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
    this->m_initWorldPosition = pos;
    this->m_worldPosition = pos;
    this->setPosition(Vec2(pos.x * PER_TILE_SIZE, (MAP_TILE_HEGHT - pos.y - 1) * PER_TILE_SIZE));
    this->m_initDirectcion = direction;
    this->setDirectcion(direction);
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
    MoveTo *actionMove = MoveTo::create(duration, Vec2(newPosition.x * PER_TILE_SIZE,  (MAP_TILE_HEGHT - newPosition.y - 1) * PER_TILE_SIZE));
    actionMove->setTag(::move);
    this->stopActionByTag(::move);
    this->runAction(actionMove);
}


/**
    スプライトが向いている方向の次のタイルのワールド座標を返す
    端にいた場合、-1,-1で返す
 
    @return スプライトが向いている方向の次のタイルのワールド座標
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
    スプライトの右隣のワールド座標を返す
 
    @return スプライトが向いている方向の右隣のワールド座標
 */
Vec2 GameSpriteBase::rightTilePosition()
{
    Vec2 rightTilePosition;
    switch (this->m_directcion) {
        case ::back:
            rightTilePosition = Vec2 { this->m_worldPosition.x + 1.0f, this->m_worldPosition.y };
            break;
        case ::right:
            rightTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + 1.0f };
            break;
        case ::front:
            rightTilePosition = Vec2 { this->m_worldPosition.x - 1.0f , this->m_worldPosition.y };
            break;
        case ::left:
            rightTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f };
            break;
        default:
            break;
    }
    return rightTilePosition;
}


/**
    スプライトの左隣のワールド座標を返す
 
    @return スプライトが向いている方向の左隣のワールド座標
 */
Vec2 GameSpriteBase::leftTilePosition()
{
    Vec2 leftTilePosition;
    switch (this->m_directcion) {
        case ::back:
            leftTilePosition = Vec2 { this->m_worldPosition.x - 1.0f, this->m_worldPosition.y };
            break;
        case ::right:
            leftTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - 1.0f };
            break;
        case ::front:
            leftTilePosition = Vec2 { this->m_worldPosition.x + 1.0f , this->m_worldPosition.y };
            break;
        case ::left:
            leftTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + 1.0f };
            break;
        default:
            break;
    }
    return leftTilePosition;
}


/**
    右に回転する
 */
void GameSpriteBase::turnRight()
{
    Vec2 rightTilePosition = this->rightTilePosition();
    this->facingNextPos(rightTilePosition);
}


/**
    左に回転する
 */
void GameSpriteBase::turnLeft()
{
    Vec2 leftTilePosition = this->leftTilePosition();
    this->facingNextPos(leftTilePosition);
}


/**
    反対方向を向く
 */
void GameSpriteBase::lookback()
{
    switch (this->m_directcion) {
        case ::front:
            this->setDirectcion(::back);
            break;
        case ::right:
            this->setDirectcion(::left);
            break;
        case ::back:
            this->setDirectcion(::front);
            break;
        case ::left:
            this->setDirectcion(::right);
            break;
        default:
            break;
    }
}


/**
    与えられた座標が移動可能かどうか
 
    @param pos 対象の座標
    @return 移動可能かどうか
 */
bool GameSpriteBase::canMovePos(Vec2 const& pos)
{
    StageSceneBase* scene = (StageSceneBase*)this->getParent();
    TMXLayer* layer = scene->m_map->getLayer("MAP");
    if (pos.x < 0.0f || pos.x >= MAP_TILE_WIDTH ||
        pos.y < 0.0f || pos.y >= MAP_TILE_HEGHT ||
        !(layer->getTileGIDAt(pos) - 1.0f == 0 ||
        layer->getTileGIDAt(pos) - 1.0f == 3)) {
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
        StageSceneBase* scene = (StageSceneBase*)this->getParent();
        TMXLayer* layer = scene->m_map->getLayer("MAP");
        tileGID = layer->getTileGIDAt(nextTilePosition) - 1;
    }
    
    return tileGID;
}
