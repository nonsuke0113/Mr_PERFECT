//
//  TitleScene.hpp
//  tannoGame
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
    
    void touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
public:
    
    static Scene* createScene();
    CREATE_FUNC(TitleScene);
    virtual bool init();
};

#endif /* TitleScene_hpp */
