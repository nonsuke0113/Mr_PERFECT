//
//  Stage19Scene.hpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#ifndef Stage19Scene_hpp
#define Stage19Scene_hpp

#include "StageSceneBase.hpp"

class Stage19Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage19Scene *createScene();
    
};

#endif /* Stage19Scene_hpp */
