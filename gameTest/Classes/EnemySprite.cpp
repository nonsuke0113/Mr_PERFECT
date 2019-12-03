//
//  EnemySprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/11/08.
//

#include "EnemySprite.hpp"
#include "MainGameScene.hpp"
#include <algorithm>
#include <unistd.h>

/**
    CharacterSprite::createメソッドをオーバーライド
 
    @param filename 敵キャラクターの画像リソース名
    @param pos 敵キャラクターのワールド座標初期位置
    @param map 敵キャラクターが配置されているマップ
    @param moveSpeed 敵キャラクターの移動速度
    @return 敵キャラクターのSprite
 */
EnemySprite* EnemySprite::create(const std::string& filename, const Vec2& pos, TMXTiledMap* map, float moveSpeed)
{
    EnemySprite *sprite = (EnemySprite*)CharacterSprite::create(filename, pos, map, moveSpeed);
    if (sprite)
    {
        sprite->m_rotateDirectcion = ::turn_right;
        return sprite;
    }
    return nullptr;
}


/**
    巡回をスケジュール
 */
void EnemySprite::startPatrol() {
    // 巡回をスケジュール
    schedule(schedule_selector(EnemySprite::rotatePatrol), 0.5f);
}


/**
    巡回を中止
 */
void EnemySprite::stopPatrol() {
    // 巡回を中止
    unschedule(schedule_selector(EnemySprite::rotatePatrol));
}


/**
    巡回する
    移動できないようになるまで、向いている方向でまっすぐ進む
    移動できなくなったら、設定された方向に回転する
 */
void EnemySprite::rotatePatrol(float frame) {
    
    if (this->checkFindPlayer()) {
        this->stopPatrol();
        MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
        mainScene->enemyFindPlayer();
    }
    
    if (this->nextTileGID() == 0) {
        this->moveNextTile();
    } else {
        this->rotate();
    }
}


/**
    設定された回転方向に応じて、向いている方向を変える
 */
void EnemySprite::rotate() {
    
    if (this->m_rotateDirectcion == ::turn_right) {
        switch (this->m_characterDirectcion) {
            case ::character_front:
                this->setCharacterDirectcion(::character_right);
                break;
            case ::character_right:
                this->setCharacterDirectcion(::character_back);
                break;
            case ::character_back:
                this->setCharacterDirectcion(::character_left);
                break;
            case ::character_left:
                this->setCharacterDirectcion(::character_front);
                break;
            default:
                break;
        }
    } else {
        switch (this->m_characterDirectcion) {
            case ::character_front:
                this->setCharacterDirectcion(::character_left);
                break;
            case ::character_right:
                this->setCharacterDirectcion(::character_front);
                break;
            case ::character_back:
                this->setCharacterDirectcion(::character_right);
                break;
            case ::character_left:
                this->setCharacterDirectcion(::character_back);
                break;
            default:
                break;
        }
    }
}


/**
    敵キャラクターが向いている方向に、プレイヤーがいるかどうかを確認する
 
    @return プレイヤーを発見したかどうか
 */
bool EnemySprite::checkFindPlayer() {
    
    Vec2 checkTilePosition;
    MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
    CharacterSprite* player = mainScene->pPlayer;
    
    for (int i = 1; i < std::max(MAP_TILE_HEGHT, MAP_TILE_WIDTH); i++) {
        
        switch (this->m_characterDirectcion) {
            case ::character_front:
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y + i };
                break;
            case ::character_right:
                checkTilePosition = Vec2 { this->m_worldPosition.x + i, this->m_worldPosition.y };
                break;
            case ::character_back:
                checkTilePosition = Vec2 { this->m_worldPosition.x, this->m_worldPosition.y - i };
                break;
            case ::character_left:
                checkTilePosition = Vec2 { this->m_worldPosition.x - i, this->m_worldPosition.y };
                break;
            default:
                break;
        }
        
        if (!this->canMovePos(checkTilePosition)) {
            return false;
        }
        
        if (player->worldPosition() == checkTilePosition) {
            return true;
        }
    }
    
    return false;
}


/**
    現在地から目的地までの最短経路を探索する
    参照渡しにて経路のスタックを書き換える
 
    @param routeStack 現在の経路スタック
    @param shortestRouteStack 現在の最短経路スタック
    @param currentPos 現在地
    @param destinationPos 目的地
 */
void EnemySprite::searchShortestRoute(std::vector<Vec2>& routeStack,
                                      std::vector<Vec2>& shortestRouteStack,
                                      const Vec2& currentPos,
                                      const Vec2& destinationPos)
{
    // 現在地を経路スタックにプッシュ
    routeStack.push_back(currentPos);
    
    // ゴールしているかどうか
    if (currentPos == destinationPos) {
        // 最短経路であれば保存する
        if (shortestRouteStack.empty() || routeStack.size() < shortestRouteStack.size()) {
            shortestRouteStack = routeStack;
            routeStack.pop_back();
            return;
        }
    }
    
    // 既に最短経路の移動数を超えている場合、何もしない
    if (!shortestRouteStack.empty() && routeStack.size() >= shortestRouteStack.size()) {
        routeStack.pop_back();
        return;
    }
    
    // 経路探索
    // 上
    Vec2 upPos = Vec2 { currentPos.x, currentPos.y - 1.0f};
    if (this->canMovePos(upPos) && std::find(routeStack.begin(), routeStack.end(), upPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, upPos, destinationPos);
    }
    // 右
    Vec2 rightPos = Vec2 { currentPos.x + 1.0f, currentPos.y };
    if (this->canMovePos(rightPos) && std::find(routeStack.begin(), routeStack.end(), rightPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, rightPos, destinationPos);
    }
    // 下
    Vec2 downPos = Vec2 { currentPos.x, currentPos.y + 1.0f};
    if (this->canMovePos(downPos) && std::find(routeStack.begin(), routeStack.end(), downPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, downPos, destinationPos);
    }
    // 左
    Vec2 leftPos = Vec2 { currentPos.x - 1.0f, currentPos.y };
       if (this->canMovePos(leftPos) && std::find(routeStack.begin(), routeStack.end(), leftPos) == routeStack.end()) {
        this->searchShortestRoute(routeStack, shortestRouteStack, leftPos, destinationPos);
    }

    routeStack.pop_back();
}


/**
    与えられた経路で移動を開始する
 
    @param routeStack 移動経路
 */
void EnemySprite::startMoveAccordingToRouteStack(const std::vector<Vec2>& routeStack)
{
    // 巡回は中断する
    this->stopPatrol();
    
    this->m_routeStack = new (std::nothrow) std::vector<Vec2>(routeStack);
    this->m_routeStackIndex = 0;
    schedule(schedule_selector(EnemySprite::moveAccordingToRouteStack), 0.5f);
}


/**
    経路に従う移動を停止する
 */
void EnemySprite::stopMoveAccordingToRouteStack()
{
    this->m_routeStackIndex = 0;
    unschedule(schedule_selector(EnemySprite::moveAccordingToRouteStack));
    
    // 再度巡回する
    this->startPatrol();
}


/**
    経路に従って移動する
 */
void EnemySprite::moveAccordingToRouteStack(float frame)
{
    if (this->m_routeStack->empty() || this->m_routeStack->size() <= this->m_routeStackIndex) {
        this->stopMoveAccordingToRouteStack();
        return;
    }
    
    Vec2 nextPos = this->m_routeStack->at(this->m_routeStackIndex);
    this->facingNextPos(nextPos);
    
    if (this->checkFindPlayer()) {
        this->stopMoveAccordingToRouteStack();
        MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
        mainScene->enemyFindPlayer();
        return;
    }
    
    this->moveWorld(this->m_moveSpeed, nextPos);
    this->m_routeStackIndex++;
}
