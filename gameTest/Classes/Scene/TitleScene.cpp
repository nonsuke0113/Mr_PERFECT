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
    this->logo = Sprite::create("title_logo.png");
    this->logo->setPosition(Vec2(visibleSize.width / 2, 480));
    this->addChild(this->logo);

    // スタートボタン
    this->startButton = ui::Button::create("start_button.png");
    this->startButton->setPosition(Vec2(visibleSize.width / 2, 160));
    this->addChild(this->startButton);
    this->startButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchStartEvent, this));
    
    // 最初からボタン(仮)
//    ui::Button* restartButton { ui::Button::create("CloseSelected.png") };
//    restartButton->setPosition(Vec2(visibleSize.width / 2, 100.0f));
//    restartButton->setTag(1);
//    this->addChild(restartButton);
//    restartButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchEvent, this));
    
    return true;
}


#pragma mark -
#pragma mark Event
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
            this->startButton->setVisible(false);
            
            // 画面サイズ取得
            Size visibleSize { Director::getInstance()->getVisibleSize() };
            
            // ミッションモードボタン
            this->menu1Button = ui::Button::create("main_menu1.png");
            this->menu1Button->setPosition(Vec2(visibleSize.width / 2, 220));
            this->addChild(this->menu1Button);
            this->menu1Button->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchMissionModeEvent, this));
            
            // 遊び方ボタン
            this->menu2Button = ui::Button::create("main_menu2.png");
            this->menu2Button->setPosition(Vec2(visibleSize.width / 2, 100));
            this->addChild(this->menu2Button);
            this->menu2Button->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchHowToPlayEvent, this));
            
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
            this->menu1Button->setVisible(false);
            this->menu2Button->setVisible(false);
            
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
