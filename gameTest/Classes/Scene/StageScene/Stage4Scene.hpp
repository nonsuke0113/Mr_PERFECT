//
//  Stage4Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/21.
//

#ifndef Stage4Scene_hpp
#define Stage4Scene_hpp

#include "StageSceneBase.hpp"

class Stage4Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void gameStart();
    void doContinue();
    void checkState();
    void stageClear();
    
public:
    static Stage4Scene *createScene();
    
};

#endif /* Stage4Scene_hpp */
