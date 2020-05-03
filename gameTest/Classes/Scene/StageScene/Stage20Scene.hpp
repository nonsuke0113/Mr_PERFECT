//
//  Stage20Scene.hpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#ifndef Stage20Scene_hpp
#define Stage20Scene_hpp

#include "StageSceneBase.hpp"

class Stage20Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage20Scene *createScene();
    
};

#endif /* Stage20Scene_hpp */
