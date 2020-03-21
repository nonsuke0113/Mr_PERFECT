//
//  TitleScene.hpp
//  tannoGame
//
//  タイトルシーン
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleScene : public Layer
{
private:
    Sprite *m_logo; // タイトルロゴ
    ui::Button *m_startButton; // スタートボタン
    ui::Button *m_menu1Button; // ミッションモードボタン
    ui::Button *m_menu2Button; // 遊び方ボタン
    
    void touchStartEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchMissionModeEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchHowToPlayEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
public:
    static Scene* createScene();
    CREATE_FUNC(TitleScene);
    virtual bool init();
    
};

#endif /* TitleScene_hpp */
