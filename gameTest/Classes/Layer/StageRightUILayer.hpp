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
    
    Sprite *background; // 背景
    ui::Button *aButton; // Aボタン
    ui::Button *bButton; // Bボタン
    
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);

public:
    
    CREATE_FUNC(StageRightUILayer);
    virtual bool init();
    
};
#endif /* StageRightUILayer_hpp */
