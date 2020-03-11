//
//  GameSpriteBase.hpp
//  gameTest-mobile
//
//  ゲーム中のスプライトの基底クラス
//
//  Created by 丹野健介 on 2019/12/10.
//

#ifndef GameSpriteBase_hpp
#define GameSpriteBase_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Const.hpp"

// 向き
typedef enum {
    back,
    right,
    front,
    left,
    none
} directcion;

// アクション
typedef enum {
    move,
    animate
} actutionTag;

class GameSpriteBase : public Sprite
{
protected:
    Vec2 m_worldPosition; // ワールド座標
    ::directcion m_directcion; // スプライトの向き
    
public:
    static GameSpriteBase* create(const std::string& filename, const Vec2 &pos, ::directcion direction);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction);
    Vec2& worldPosition();
    directcion directcion();
    void setWorldPosition(Vec2& worldPos);
    virtual void setDirectcion(::directcion direction);
    void moveWorld(float duration, const Vec2& newPosition);
    Vec2 nextTilePosition();
    int nextTileGID();
    bool canMovePos(Vec2& pos);
    void facingNextPos(Vec2& pos);
    
};

#endif /* GameSpriteBase_hpp */
