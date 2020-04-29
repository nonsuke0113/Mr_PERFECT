//
//  Stage16Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/20.
//

#ifndef Stage16Scene_hpp
#define Stage16Scene_hpp

#include "StageSceneBase.hpp"
#include "ReactsHitSprite.hpp"

class Stage16Scene : public StageSceneBase
{
private:
    /// 出口を隠す用の壁
    GameSpriteBase *m_wall;
    /// ターゲット
    ReactsHitSprite *m_target1;
    
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    void hitTarget1();
    
public:
    static Stage16Scene *createScene();
    
};

#endif /* Stage16Scene_hpp */
