//
//  Stage3Scene.hpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2020/03/21.
//

#ifndef Stage3Scene_hpp
#define Stage3Scene_hpp

#include "StageSceneBase.hpp"

class Stage3Scene : public StageSceneBase
{
private:
    /// チュートリアルメッセージ3表示済みかどうか
    bool m_isTutorialMessage3;
    
    void initStage();
    void initMap();
    void initCharactors();
    void initScoreStandard();
    void gameStart();
    void doContinue();
    void checkState();
    void createTutorialMessage3();
    
public:
    static Stage3Scene *createScene();
    
};

#endif /* Stage3Scene_hpp */
