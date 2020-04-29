//
//  Stage7Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#ifndef Stage7Scene_hpp
#define Stage7Scene_hpp

#include "StageSceneBase.hpp"

class Stage7Scene : public StageSceneBase
{
private:
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    
public:
    static Stage7Scene *createScene();
    
};

#endif /* Stage7Scene_hpp */
