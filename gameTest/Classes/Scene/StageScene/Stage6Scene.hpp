//
//  Stage6Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef Stage6Scene_hpp
#define Stage6Scene_hpp

#include "StageSceneBase.hpp"

class Stage6Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage6Scene *createScene();
    
};

#endif /* Stage6Scene_hpp */
