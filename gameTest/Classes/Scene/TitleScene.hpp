//
//  TitleScene.hpp
//  tannoGame
//
//  タイトルシーン
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayerSprite.hpp"
#include "EnemySprite.hpp"

class TitleScene : public Layer
{
private:
    /// タイトルロゴ
    Sprite *m_logo;
    /// スタートボタン
    ui::Button *m_startButton;
    /// ミッションモードボタン
    ui::Button *m_menu1Button;
    /// 遊び方ボタン
    ui::Button *m_menu2Button;
    /// クレジットボタン
    ui::Button *m_menu3Button;
    /// プレイヤーキャラクター
    PlayerSprite *m_playerSprite;
    /// 敵キャラクター
    EnemySprite *m_enemySprite;
    
    void touchStartEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchMissionModeEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchHowToPlayEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchCreditEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void update(float delta);
    void updateCharactorPosition(CharacterSprite *charactor);
    
public:
    static Scene* createScene();
    CREATE_FUNC(TitleScene);
    virtual bool init();
    
};

#endif /* TitleScene_hpp */
