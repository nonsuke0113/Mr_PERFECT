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

#include "CharacterSprite.hpp"
#include "EnemySprite.hpp"
#include "MessageDialog.hpp"

// 十字ボタン状態
typedef enum {
    pushedButtonNone,
    isPushedUpButton,
    isPushedRightButton,
    isPushedDownButton,
    isPushedLeftButton
} pushedButton;


class StageSceneBase : public Scene
{
protected:
    Camera* m_camera;    // スクロール用カメラ
    Label* m_playerMapPointLabel { nullptr }; // 操作キャラクター座標ラベル(デバッグ用)
    MessageDialog* m_messageDialog  { nullptr };   // メッセージダイアログ
    pushedButton m_isPushedButton;  // 十字ボタンの状態
    
    void initCamera();
    void initUI();
    virtual void initMap();
    virtual void initCharactors();
    
public:
    static Scene* createScene();
    virtual bool init();
    
};

#endif /* StageSceneBase_hpp */
