//
//  Stage11Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/21.
//

#ifndef Stage11Scene_hpp
#define Stage11Scene_hpp

#include "StageSceneBase.hpp"

class Stage11Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage11Scene *createScene();
    
};

#endif /* Stage11Scene_hpp */
