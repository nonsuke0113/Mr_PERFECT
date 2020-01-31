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
protected:
    void initMap();
    void initCharactors();
    void doContinue();
public:
    static Stage1Scene *createScene();
};

#endif /* Stage1Scene_hpp */
