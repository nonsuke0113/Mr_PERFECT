//
//  MainGameScene.hpp
//  tannoGame
//
//  メインシーン
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#ifndef MainGameScene_hpp
#define MainGameScene_hpp

USING_NS_CC;

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "CharacterSprite.hpp"
#include "EnemySprite.hpp"
#include "MessageDialog.hpp"

// 十字ボタン状態
//typedef enum {
//    pushedButtonNone,
//    isPushedUpButton,
//    isPushedRightButton,
//    isPushedDownButton,
//    isPushedLeftButton
//} pushedButton;
//
//// メッセージの種類
//typedef enum {
//    nomal,
//    save,
//    findPlayer
//} messageType;


class MainGameScene : public Layer
{
protected:
    
    Camera* m_camera;    // スクロール用カメラ
    Label* m_playerMapPointLabel { nullptr }; // 操作キャラクター座標ラベル(デバッグ用)
    MessageDialog* m_messageDialog  { nullptr };   // メッセージダイアログ
//    pushedButton m_isPushedButton;  // 十字ボタンの状態
    
    void initUI();
    virtual void initCharactor();
    
    void touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchA2Event(Ref *pSender, ui::Widget::TouchEventType type);
    void touchSaveEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
//    void createMessageDialog(::messageType messageType);
    void createMessage();
    void createSaveMessage();
    void createFindPlayerMessage();
    void setMessageCallback();
    void gameover();
    void doSave();
    void doContinue();
    void updatePosition(float frame);
    void updateCameraPosition();
    
public:
    
    TMXTiledMap* m_map;  // MAP
    CharacterSprite* m_player;   // 操作キャラクター
    
    static Scene* createScene();
    CREATE_FUNC(MainGameScene);
    virtual bool init();
    
    Vector<CharacterSprite*> charactersVector();
    Vector<EnemySprite*> enemysVector();
    void enemyFindPlayer();
    void hitEnemy(EnemySprite* enemy);
};

#endif /* MainGameScene_hpp */
