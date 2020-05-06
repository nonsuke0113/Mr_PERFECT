//
//  Stage16Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#ifndef Stage16Scene_hpp
#define Stage16Scene_hpp

#include "StageSceneBase.hpp"

class Stage16Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage16Scene *createScene();
    
};

#endif /* Stage16Scene_hpp */
