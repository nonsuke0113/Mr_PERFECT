//
//  EnemySprite.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/11/08.
//

#include "EnemySprite.hpp"
#include "MainGameScene.hpp"

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
    設定された周りで、向いている方向を変える
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
    TMXLayer* layer = this->m_map->getLayer("MAP");
    int tileGID = -1;
    MainGameScene* mainScene = (MainGameScene*)this->m_map->getParent();
    CharacterSprite* player = mainScene->pPlayer;
    
    // 
    for (int i = 1; i < 20; i++) {
        
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
        
        tileGID = layer->getTileGIDAt(checkTilePosition) - 1;
        if (tileGID != 0) {
            return false;
        }
        
        if (player->worldPosition() == checkTilePosition) {
            return true;
        }
    }
    
    return false;
}
