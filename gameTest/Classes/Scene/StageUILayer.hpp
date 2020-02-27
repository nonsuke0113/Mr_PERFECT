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

typedef enum {
    padNone,
    padUp,
    padRight,
    padDown,
    padLeft
} padState;

class StageUILayer : public Layer
{
private:
    
    Sprite *padBack; // パッド下地
    Sprite *padPick; // パッド操作部
    
    double degreeFromVec2(Vec2 posA, Vec2 posB);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
public:

    CREATE_FUNC(StageUILayer);
    virtual bool init();
    
    ::padState padState();
};

#endif /* StageUILayer_hpp */
