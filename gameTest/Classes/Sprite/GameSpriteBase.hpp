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
#include "GameConst.hpp"

/// 向き
typedef enum {
    back,
    right,
    front,
    left,
    none
} directcion;

/// アクション
typedef enum {
    move,
    animate
} actutionTag;

class GameSpriteBase : public Sprite
{
protected:
    /// 初期座標
    Vec2 m_initWorldPosition;
    /// ワールド座標
    Vec2 m_worldPosition;
    /// スプライトの初期の向き
    ::directcion m_initDirectcion;
    /// スプライトの向き
    ::directcion m_directcion;
    /// 他のスプライトが通過可能かどうか
    bool m_isThroughable;
    
public:
    static GameSpriteBase* create(const std::string& filename, const Vec2 &pos, ::directcion direction, bool isThroughable);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, bool isThroughable);
    Vec2& worldPosition();
    directcion directcion();
    bool isThroughable();
    void setWorldPosition(Vec2 const& worldPos);
    virtual void setDirectcion(::directcion direction);
    void moveWorld(Vec2 const& newPosition);
    Vec2 nextTilePosition();
    Vec2 rightTilePosition();
    Vec2 leftTilePosition();
    void turnRight();
    void turnLeft();
    void lookback();
    int nextTileGID();
    bool canMovePos(Vec2 const& pos);
    void facingNextPos(Vec2& pos);
    
};

#endif /* GameSpriteBase_hpp */
