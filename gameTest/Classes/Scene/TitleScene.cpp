//
//  TitleScene.cpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#include "TitleScene.hpp"
#include "StageSceneBase.hpp"
#include "Stage1Scene.hpp"
#include "SelectMissonScene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}


/**
    初期化処理
 */
bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    
    // 背景
    Sprite *bgSprite { Sprite::create("title_background.png") };
    bgSprite->setPosition(visibleSize / 2);
    this->addChild(bgSprite);
    
    // ロゴ
    this->m_logo = Sprite::create("title_logo.png");
    this->m_logo->setPosition(Vec2(visibleSize.width / 2, 480));
    this->addChild(this->m_logo);

    // スタートボタン
    this->m_startButton = ui::Button::create("start_button.png");
    this->m_startButton->setPosition(Vec2(visibleSize.width / 2, 160));
    this->addChild(this->m_startButton);
    this->m_startButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchStartEvent, this));
    
    return true;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    スタートボタン押下時のイベント
 */
void TitleScene::touchStartEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    ui::Button *button = (ui::Button*)pSender;
    if(button->getTag() == 1) {
        UserDefault* userDefault = UserDefault::getInstance();
        userDefault->setStringForKey("playerName", "");
    }
    
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            this->m_startButton->setVisible(false);
            
            // 画面サイズ取得
            Size visibleSize { Director::getInstance()->getVisibleSize() };
            
            // ミッションモードボタン
            this->m_menu1Button = ui::Button::create("main_menu1.png");
            this->m_menu1Button->setPosition(Vec2(visibleSize.width / 2, 220));
            this->addChild(this->m_menu1Button);
            this->m_menu1Button->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchMissionModeEvent, this));
            
            // 遊び方ボタン
            this->m_menu2Button = ui::Button::create("main_menu2.png");
            this->m_menu2Button->setPosition(Vec2(visibleSize.width / 2, 100));
            this->addChild(this->m_menu2Button);
            this->m_menu2Button->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchHowToPlayEvent, this));
            
            break;
        }
        default:
            break;
    }
}


/**
    ミッションモードボタン押下時のイベント
 */
void TitleScene::touchMissionModeEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            Scene *selectMissionScene { SelectMissonScene::createScene() };
            Director::getInstance()->replaceScene(selectMissionScene);
            break;
        }
        default:
            break;
    }
}


/**
    遊び方ボタン押下時のイベント
 */
void TitleScene::touchHowToPlayEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            this->m_menu1Button->setVisible(false);
            this->m_menu2Button->setVisible(false);
            
            // 画面サイズ取得
            Size visibleSize { Director::getInstance()->getVisibleSize() };
            
            // 遊び方スプライト配置
            Sprite *howToPlay { Sprite::create("title_background.png") };
            howToPlay->setPosition(visibleSize / 2);
            this->addChild(howToPlay);
            
            break;
        }
        default:
            break;
    }
}
