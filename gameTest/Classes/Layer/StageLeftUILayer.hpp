//
//  StageLeftUILayer.hpp
//  gameTest-mobile
//
//  ステージの左サイドバーのUIレイヤー
//
//  Created by 丹野健介 on 2020/02/29.
//

#ifndef StageLeftUILayer_hpp
#define StageLeftUILayer_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

// バーチャルパッドステータス一覧
typedef enum {
    padNone,
    padUp,
    padRight,
    padDown,
    padLeft
} padState;


class StageLeftUILayer : public Layer
{
private:
    
    Sprite *background; // 背景
    Sprite *padBack; // パッド下地
    Sprite *padPick; // パッド操作部
    Vector<Sprite*> heartes; // hp
    
    static double degreeFromVec2(Vec2 posA, Vec2 posB);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
public:
    
    CREATE_FUNC(StageLeftUILayer);
    virtual bool init();
    
    ::padState padState();
    void heartOff(int i);
};

#endif /* StageLeftUILayer_hpp */
