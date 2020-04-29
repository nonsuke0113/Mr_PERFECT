//
//  Stage1Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/18.
//

#ifndef Stage1Scene_hpp
#define Stage1Scene_hpp

#include "StageSceneBase.hpp"

class Stage1Scene : public StageSceneBase
{
private:
    /// チュートリアルメッセージ1表示済みかどうか
    bool m_isTutorialMessage1;
    
    void initStage();
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void touchA();
    void touchB();
    void enemyFoundPlayer();
    void doContinue();
    void checkState();
    void createTutorialMessage1();
    
public:
    static Stage1Scene *createScene();
    
};

#endif /* Stage1Scene_hpp */
