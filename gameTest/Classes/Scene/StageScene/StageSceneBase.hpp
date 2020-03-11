//
//  StageSceneBase.hpp
//  gameTest-mobile
//
//  ゲームの1ステージシーンの基底クラス
//
//  Created by 丹野健介 on 2019/12/17.
//

#ifndef StageSceneBase_hpp
#define StageSceneBase_hpp

USING_NS_CC;

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayerSprite.hpp"
#include "EnemySprite.hpp"
#include "MessageDialog.hpp"
#include "AdMobHelper.h"
#include "StageUILayer.hpp"

// メッセージの種類
typedef enum {
    nomal,
    failed
} messageType;

class StageSceneBase : public Scene
{
private:
    void initCamera();
    void initUI();
    void initStart();
    void gameover();
    void updateTime();
    void updatePosition();
    void updateCameraPosition();
    
protected:
    float m_time; // 経過時間
    Camera *m_camera; // スクロール用カメラ
    MessageDialog *m_messageDialog; // メッセージダイアログ
    StageUILayer *m_uiLayer; // UIレイヤー
    
    virtual void initMap();
    virtual void initCharactors();
    void createMessageDialog(::messageType messageType);
    void createMessage();
    void createMissionFailedMessage();
    void setMessageCallback();
    void allNodeUnschedule();
    virtual void stageClear();
    virtual void doContinue();
    virtual void update(float delta);
    virtual void checkPosition();
    
public:
    TMXTiledMap *m_map; // MAP
    PlayerSprite *m_player; // 操作キャラクター
    
    static StageSceneBase *createScene();
    virtual bool init();
    ::padState padState();
    Vector<CharacterSprite*> charactersVector();
    Vector<EnemySprite*> enemysVector();
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void missionFailed();
    void enemyFindPlayer();
    void heartOff(int i);
    
};

#endif /* StageSceneBase_hpp */
