//
//  Stage11Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/29.
//

#ifndef Stage11Scene_hpp
#define Stage11Scene_hpp

#include "StageSceneBase.hpp"

class Stage11Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void gameStart();
    void doContinue();
    void checkState();
    void warpIfNeed();
    void stageClear();
    
public:
    static Stage11Scene *createScene();
    
};

#endif /* Stage11Scene_hpp */
