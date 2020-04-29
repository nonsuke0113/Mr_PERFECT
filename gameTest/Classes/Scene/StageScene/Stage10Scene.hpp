//
//  Stage10Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#ifndef Stage10Scene_hpp
#define Stage10Scene_hpp

#include "StageSceneBase.hpp"

class Stage10Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage10Scene *createScene();
    
};

#endif /* Stage10Scene_hpp */
