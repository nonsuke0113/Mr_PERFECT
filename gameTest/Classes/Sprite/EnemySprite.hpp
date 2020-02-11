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
    turn_left
} rotateDirectcion;


class EnemySprite : public CharacterSprite
{
protected:
    ::rotateDirectcion m_rotateDirectcion; // 巡回時の回転方向
    
    std::vector<Vec2>* m_routeStack; // 経路
    int m_routeStackIndex; // 経路の進捗を管理するインデックス
    
    std::vector<Vec2> n_routeStack;
    Vec2 m_playerLostPoint;
    Vec2 m_playerLostNextPoint;
    
    void setupAnimationCache();
    
    void setDirectcion(::directcion direction);
    
    void hitToBullet(int damage, ::directcion bulletDirection);
    void dead();
    
    void rotatePatrol(float frame);
    void rotate();
    bool checkFindPlayer();
    
    void moveAccordingToRouteStack(float frame);
    void chasePlayer(float frame);
    void shoot(float frame);
    
public:
    static EnemySprite* create(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, float moveSpeed);
    
    void startPatrol();
    void stopPatrol();
    void startMoveAccordingToRouteStack(const std::vector<Vec2>& routeStack);
    void stopMoveAccordingToRouteStack();
    void startChasePlayer();
    void stopChasePlayer();
    void startShoot();
    void stopShoot();
    void loseSightOfPlayer();
};

#endif /* EnemySprite_hpp */
