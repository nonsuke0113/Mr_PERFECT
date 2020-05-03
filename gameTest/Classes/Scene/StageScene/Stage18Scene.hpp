//
//  Stage18Scene.hpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#ifndef Stage18Scene_hpp
#define Stage18Scene_hpp

#include "StageSceneBase.hpp"
#include "ReactsHitSprite.hpp"

class Stage18Scene : public StageSceneBase
{
private:
    /// スイッチ
    GameSpriteBase *m_switch1;
    GameSpriteBase *m_switch2;
    
    /// 壁
    GameSpriteBase *m_wall;
    
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    void touchA();
    
public:
    static Stage18Scene *createScene();
    
};

#endif /* Stage18Scene_hpp */
