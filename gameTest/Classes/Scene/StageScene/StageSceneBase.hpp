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
    save,
    findPlayer
} messageType;


class StageSceneBase : public Scene
{
protected:
    Camera *m_camera;    // スクロール用カメラ
    Label *m_playerMapPointLabel { nullptr }; // 操作キャラクター座標ラベル(デバッグ用)
    MessageDialog *m_messageDialog  { nullptr };   // メッセージダイアログ
    StageUILayer *m_uiLayer; // UIレイヤー
    
    void initCamera();
    void initUI();
    virtual void initMap();
    virtual void initCharactors();
    void initStart();
    
    void touchSaveEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
    void createMessageDialog(::messageType messageType);
    void createMessage();
    void createSaveMessage();
    void createFindPlayerMessage();
    void setMessageCallback();
    
    void stageClear();
    
    void gameover();
    void doSave();
    virtual void doContinue();
    
    virtual void checkClear(float frame);
    void updatePosition(float frame);
    void updateCameraPosition();
    
public:
    TMXTiledMap *m_map;  // MAP
    PlayerSprite *m_player;   // 操作キャラクター
    
    static StageSceneBase *createScene();
    virtual bool init();
    
    Vector<CharacterSprite*> charactersVector();
    Vector<EnemySprite*> enemysVector();
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void enemyFindPlayer();
};

#endif /* StageSceneBase_hpp */
