//
//  SelectMissonScene.hpp
//  gameTest-mobile
//
//  ミッション選択シーン
//
//  Created by 丹野健介 on 2020/01/31.
//

#ifndef SelectMissonScene_hpp
#define SelectMissonScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SelectMissonScene : public Layer
{
private:
    void touchMissionEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
public:
    static Scene* createScene();
    CREATE_FUNC(SelectMissonScene);
    virtual bool init();
    
};

#endif /* SelectMissonScene_hpp */
