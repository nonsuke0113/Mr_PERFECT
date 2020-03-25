//
//  EnemySprite.hpp
//  gameTest-mobile
//
//  敵キャラクターのクラス
//
//  Created by 丹野健介 on 2019/11/08.
//

#ifndef EnemySprite_hpp
#define EnemySprite_hpp

#include "CharacterSprite.hpp"
#include <vector>

// 回転方向
typedef enum {
    turn_right,
    turn_left,
    turn_none
} rotateDirectcion;

// 警備の種類
typedef enum {
    patorol_roundtrip, // 往復
    patorol_rotate, // 巡回
    patorol_chase, // 追跡中
    patorol_according, // 経路に沿って移動中
    patorol_nomove, // 移動なし
    patorol_none // 警備なし
} patorolType;

// 吹き出しの種類
typedef enum {
    exclamation,
    question
} speechBubbleType;


class EnemySprite : public CharacterSprite
{
protected:
    Vec2 m_initPosition; // 初期座標
    ::patorolType m_patorolType; // 巡回の種類
    ::rotateDirectcion m_rotateDirection; // 巡回時の回転方向
    std::vector<Vec2> m_routeStack; // 経路
    int m_routeStackIndex; // 経路の進捗を管理するインデックス
    Vec2 m_playerLostPoint; // プレイヤーを最後に発見した座標
    Vec2 m_playerLostNextPoint; // プレイヤーを見失った際に見た次の座標
    bool m_movingHeardSoundPoint; // 聞こえた位置に移動中
    bool m_isFoundPlayer; // プレイヤー発見中
    
    void setupAnimationCache();
    void setDirectcion(::directcion direction);
    void hitToBullet(int damage, ::directcion bulletDirection);
    void dead();
    
    virtual void update(float delta);
    virtual void foundPlayer();
    virtual void losePlayer();
    virtual void patrolRoundTrip();
    virtual void patrolRotate();
    virtual void patrolChase();
    void moveToPos2(Vec2 const& pos);
    
    void patrol(float frame);
    void rotate();
    void lookback();
    bool checkFindPlayer();
    void moveAccordingToRouteStack(float frame);
    void chasePlayer(float frame);
    void shoot(float frame);
    
public:
    static EnemySprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed, ::patorolType patorolType);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed, ::patorolType patorolType);
    void setRotateDirectcion(::rotateDirectcion rotateDirection);
    void showSpeechBubble(::speechBubbleType speechBubbleType);
    void startPatrol();
    void stopPatrol();
    void moveToPos(const Vec2 &pos);
    void startMoveAccordingToRouteStack(const std::vector<Vec2>& routeStack);
    void stopMoveAccordingToRouteStack();
    void startChasePlayer();
    void stopChasePlayer();
    void startShoot();
    void stopShoot();
    void loseSightOfPlayer();
    
};

#endif /* EnemySprite_hpp */
