//
//  ResultScene.hpp
//  gameTest-mobile
//
//  リザルトシーン
//
//  Created by 丹野健介 on 2020/03/10.
//

#ifndef ResultScene_hpp
#define ResultScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StageSceneBase.hpp"

class ResultScene : public Layer
{
private:
    ResultInfo m_resultInfo; // リザルト情報
    Sprite *m_userRankSprite; // ランク画像
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void touchShareEvent(Ref *pSender, ui::Widget::TouchEventType type);
    static std::string convertRankStr(int score);
    
public:
    static Scene* createScene(ResultInfo resultInfo);
    static ResultScene* create(ResultInfo resultInfo);
    virtual bool init(ResultInfo resultInfo);
    
};

#endif /* ResultScene_hpp */
