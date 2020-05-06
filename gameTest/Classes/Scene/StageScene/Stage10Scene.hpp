//
//  Stage10Scene.hpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2020/03/21.
//

#ifndef Stage10Scene_hpp
#define Stage10Scene_hpp

#include "StageSceneBase.hpp"

class Stage10Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage10Scene *createScene();
    
};

#endif /* Stage10Scene_hpp */
