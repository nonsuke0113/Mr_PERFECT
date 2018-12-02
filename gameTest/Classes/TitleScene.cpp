//
//  TitleScene.cpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#include "TitleScene.hpp"
#include "MainGameScene.hpp"

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}


/**
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
    Sprite* bgSprite { Sprite::create("title_bg_test.png") };
    bgSprite->setPosition(visibleSize / 2);
    this->addChild(bgSprite);
    
    // スタートボタン
    ui::Button* startButton { ui::Button::create("title_start_test.png") };
    startButton->setPosition(visibleSize / 2);
    this->addChild(startButton);
    startButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchEvent, this));
    
    return true;
}


/**
 スタートボタン押下時のイベント
 */
void TitleScene::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            // MainGameSceneに遷移
            Scene* mainGameScene { MainGameScene::createScene() };
            TransitionFade* fade = TransitionFade::create(1.0f, mainGameScene);
            Director::getInstance()->replaceScene(fade);
            break;
        }
            
        default:
            break;
            
    }
}
