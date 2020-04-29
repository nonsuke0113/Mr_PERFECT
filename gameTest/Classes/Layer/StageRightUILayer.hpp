//
//  StageRightUILayer.hpp
//  gameTest-mobile
//
//  ステージの右サイドバーのUIレイヤー
//
//  Created by 丹野健介 on 2020/03/01.
//

#ifndef StageRightUILayer_hpp
#define StageRightUILayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class StageRightUILayer : public Layer
{
private:
    /// 背景
    Sprite *m_background;
    /// 時間
    Label *m_timeValueLabel;
    /// Aボタン
    ui::Button *m_aButton;
    /// Bボタン
    ui::Button *m_bButton;
    /// 一時停止ボタン
    ui::Button *m_pauseButton;
    
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchPauseEvent(Ref *pSender, ui::Widget::TouchEventType type);

public:
    CREATE_FUNC(StageRightUILayer);
    virtual bool init();
    void updateTime(float time);
    
};
#endif /* StageRightUILayer_hpp */
