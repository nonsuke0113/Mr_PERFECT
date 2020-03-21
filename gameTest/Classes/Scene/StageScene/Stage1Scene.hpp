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
    bool m_isTutorialMessage1; // チュートリアルメッセージ1表示済みかどうか
    
    void initMap();
    void initCharactors();
    void gameStart();
    void touchA();
    void touchB();
    void enemyFoundPlayer();
    void doContinue();
    void checkState();
    void stageClear();
    void setupResult();
    void createTutorialMessage1();
    
public:
    static Stage1Scene *createScene();
    
};

#endif /* Stage1Scene_hpp */
