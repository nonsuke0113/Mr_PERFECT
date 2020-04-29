//
//  Stage5Scene.hpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2020/03/21.
//

#ifndef Stage5Scene_hpp
#define Stage5Scene_hpp

#include "StageSceneBase.hpp"

class Stage5Scene : public StageSceneBase
{
private:
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage5Scene *createScene();
    
};

#endif /* Stage5Scene_hpp */
