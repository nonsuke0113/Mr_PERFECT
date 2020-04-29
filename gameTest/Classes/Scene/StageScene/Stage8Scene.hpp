//
//  Stage8Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#ifndef Stage8Scene_hpp
#define Stage8Scene_hpp

#include "StageSceneBase.hpp"

class Stage8Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage8Scene *createScene();
    
};

#endif /* Stage8Scene_hpp */
