//
//  Stage2Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/09.
//

#ifndef Stage2Scene_hpp
#define Stage2Scene_hpp

#include "StageSceneBase.hpp"

class Stage2Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void doContinue();
    void checkPosition();
    void stageClear();
    
public:
    static Stage2Scene *createScene();
    
};

#endif /* Stage2Scene_hpp */
