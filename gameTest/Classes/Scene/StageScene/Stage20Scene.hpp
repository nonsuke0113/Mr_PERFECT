//
//  Stage20Scene.hpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#ifndef Stage20Scene_hpp
#define Stage20Scene_hpp

#include "StageSceneBase.hpp"
#include "ReactsHitSprite.hpp"

class Stage20Scene : public StageSceneBase
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
    static Stage20Scene *createScene();
    
};

#endif /* Stage20Scene_hpp */
