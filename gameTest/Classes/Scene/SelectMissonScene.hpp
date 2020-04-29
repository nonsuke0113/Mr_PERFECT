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
    /// ページ
    int m_page;
    /// 進むボタン
    ui::Button *m_nextButton;
    /// 戻るボタン
    ui::Button *m_backButton;
    /// ミッション選択ボタンの配列
    Vector<ui::Button*> m_missionButtons;
    /// スコアラベルの配列
    Vector<Label*> m_scoreLabels;
    /// ランク画像の配列
    Vector<Sprite*> m_rankSprites;
    
    void initMission();
    void updateView();
    void touchMissionEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchNextEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type);
    
public:
    static Scene* createScene(int page);
    static SelectMissonScene* create(int page);
    virtual bool init(int page);
    
};

#endif /* SelectMissonScene_hpp */
