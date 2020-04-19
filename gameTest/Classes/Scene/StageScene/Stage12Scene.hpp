//
//  Stage12Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef Stage12Scene_hpp
#define Stage12Scene_hpp

#include "StageSceneBase.hpp"

class Stage12Scene : public StageSceneBase
{
private:
    void initStage();
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage12Scene *createScene();
    
};

#endif /* Stage12Scene_hpp */
