//
//  Stage18Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef Stage18Scene_hpp
#define Stage18Scene_hpp

#include "StageSceneBase.hpp"

class Stage18Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage18Scene *createScene();
    
};

#endif /* Stage18Scene_hpp */
