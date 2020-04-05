//
//  CreditScene.hpp
//  gameTest-mobile
//
//  クレジットシーン
//
//  Created by 丹野健介 on 2020/04/05.
//

#ifndef CreditScene_hpp
#define CreditScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CreditScene : public Layer
{
private:
    void touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
public:
    static Scene* createScene();
    CREATE_FUNC(CreditScene);
    virtual bool init();
    
};

#endif /* CreditScene_hpp */
