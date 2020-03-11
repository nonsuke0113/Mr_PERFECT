//
//  Stage1Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/18.
//

#ifndef Stage1Scene_hpp
#define Stage1Scene_hpp

#include "StageSceneBase.hpp"

class Stage1Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void doContinue();
    void checkPosition();
    void stageClear();
    void setupResult();
    
public:
    static Stage1Scene *createScene();
    
};

#endif /* Stage1Scene_hpp */
