//
//  Stage14Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef Stage14Scene_hpp
#define Stage14Scene_hpp

#include "StageSceneBase.hpp"

class Stage14Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage14Scene *createScene();
    
};

#endif /* Stage14Scene_hpp */
