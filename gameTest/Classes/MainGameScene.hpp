//
//  MainGameScene.hpp
//  tannoGame
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
#include "MessageDialog.hpp"

// 十字ボタン状態
typedef enum {
    pushedButtonNone,
    isPushedUpButton,
    isPushedRightButton,
    isPushedDownButton,
    isPushedLeftButton
} pushedButton;


class MainGameScene : public Layer
{
private:
    
    TMXTiledMap* pMap;  // MAP
    Camera* pCamera;    // スクロール用カメラ
    CharacterSprite* pPlayer;   // 操作キャラクター
    Label* playerMapPointLabel { nullptr }; // 操作キャラクター座標ラベル(デバッグ用)
    MessageDialog* messageDialog { nullptr };   // メッセージダイアログ
    pushedButton m_isPushedButton;  // 十字ボタンの状態
    
    void touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchSaveEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
    void createMessageDialog(bool isSave);
    void createMessage();
    void createSaveMessage();
    void setMessageCallback();
    
    void doSave();
    
    void updatePosition(float frame);
    void updateMobPosition(float frame);
    
public:
    
    std::vector<CharacterSprite*> charactersVector; //  画面内キャラクターの動的配列
    
    static Scene* createScene();
    CREATE_FUNC(MainGameScene);
    virtual bool init();
};

#endif /* MainGameScene_hpp */
