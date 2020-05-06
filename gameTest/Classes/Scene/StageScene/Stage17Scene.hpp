//
//  Stage17Scene.hpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#ifndef Stage17Scene_hpp
#define Stage17Scene_hpp

#include "StageSceneBase.hpp"
#include "ReactsHitSprite.hpp"

class Stage17Scene : public StageSceneBase
{
private:
    /// スイッチ
    GameSpriteBase *m_switch1;
    GameSpriteBase *m_switch2;
    
    /// 壁
    GameSpriteBase *m_wall1;
    GameSpriteBase *m_wall2;
    
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    void touchA();
    
public:
    static Stage17Scene *createScene();
    
};

#endif /* Stage17Scene_hpp */
