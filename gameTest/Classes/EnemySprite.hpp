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


// 回転方向
typedef enum {
    turn_right,
    turn_left
} rotateDirectcion;


class EnemySprite : public CharacterSprite
{
protected:
    ::rotateDirectcion m_rotateDirectcion; // 巡回時の回転方向
    
    void rotatePatrol(float frame);
    void rotate();
    bool checkFindPlayer();
    
public:
    static EnemySprite* create(const std::string& filename, const Vec2 &pos, TMXTiledMap* map, float moveSpeed);
    
    void startPatrol();
    void stopPatrol();
};

#endif /* EnemySprite_hpp */
