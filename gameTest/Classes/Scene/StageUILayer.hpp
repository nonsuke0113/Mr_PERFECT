//
//  StageUILayer.hpp
//  gameTest-mobile
//
//  ステージUIを配置するレイヤー
//
//  Created by 丹野健介 on 2020/02/26.
//

#ifndef StageUILayer_hpp
#define StageUILayer_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StageUILayer : public Layer
{
private:
    
    Sprite *padBack; // パッド下地
    Sprite *padPick; // パッド操作部
    
public:

    CREATE_FUNC(StageUILayer);
    virtual bool init();
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
};

#endif /* StageUILayer_hpp */
