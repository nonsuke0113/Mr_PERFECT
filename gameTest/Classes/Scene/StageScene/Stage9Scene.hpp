//
//  Stage9Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#ifndef Stage9Scene_hpp
#define Stage9Scene_hpp

#include "StageSceneBase.hpp"

class Stage9Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage9Scene *createScene();
    
};

#endif /* Stage9Scene_hpp */
