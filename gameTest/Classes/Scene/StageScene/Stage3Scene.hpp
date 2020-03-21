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
    bool m_isTutorialMessage3; // チュートリアルメッセージ3表示済みかどうか
    bool m_isfirstShootMessage; // 始めて銃を撃った時
    
    void initMap();
    void initCharactors();
    void gameStart();
    void doContinue();
    void checkPosition();
    void stageClear();
    void createTutorialMessage3();
    void firstshootMessage();
    void touchB();
    
public:
    static Stage3Scene *createScene();
    
};

#endif /* Stage3Scene_hpp */
