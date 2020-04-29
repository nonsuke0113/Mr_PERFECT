//
//  Stage17Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/23.
//

#ifndef Stage17Scene_hpp
#define Stage17Scene_hpp

#include "StageSceneBase.hpp"
#include "ReactsHitSprite.hpp"

class Stage17Scene : public StageSceneBase
{
private:
    /// 床のスイッチ
    GameSpriteBase *m_switch1;
    /// ターゲット
    ReactsHitSprite *m_target1;
    /// スイッチの状態
    bool m_isSwitch1On;
    
    void initStage();
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    void checkSwitch();
    void hitTarget1();
    
public:
    static Stage17Scene *createScene();
    
};

#endif /* Stage17Scene_hpp */
