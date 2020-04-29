//
//  Stage2Scene.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/09.
//

#ifndef Stage2Scene_hpp
#define Stage2Scene_hpp

#include "StageSceneBase.hpp"

class Stage2Scene : public StageSceneBase
{
private:
    /// チュートリアルメッセージ2表示済みかどうか
    bool m_isTutorialMessage2;
    
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void enemyFoundPlayer();
    void touchB();
    void doContinue();
    void checkState();
    void createTutorialMessage2();

public:
    static Stage2Scene *createScene();
    
};

#endif /* Stage2Scene_hpp */
