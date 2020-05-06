//
//  Stage13Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef Stage13Scene_hpp
#define Stage13Scene_hpp

#include "StageSceneBase.hpp"

class Stage13Scene : public StageSceneBase
{
private:
    /// 出口を隠す用の壁
    GameSpriteBase *m_wall;
    
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void touchA();
    void doContinue();
    void checkState();
    
public:
    static Stage13Scene *createScene();
    
};

#endif /* Stage13Scene_hpp */
