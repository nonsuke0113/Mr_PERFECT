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
    Sprite *m_background; // 背景
    Label *m_timeValueLabel; // 時間
    ui::Button *m_aButton; // Aボタン
    ui::Button *m_bButton; // Bボタン
    
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);

public:
    CREATE_FUNC(StageRightUILayer);
    virtual bool init();
    void updateTime(float time);
    
};
#endif /* StageRightUILayer_hpp */
