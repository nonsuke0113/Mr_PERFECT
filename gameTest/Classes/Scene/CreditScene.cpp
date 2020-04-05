//
//  CreditScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/05.
//

#include "CreditScene.hpp"
#include "TitleScene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Scene* CreditScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CreditScene::create();
    scene->addChild(layer);
    return scene;
}


/**
    初期化処理
 */
bool CreditScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    
    // 背景色を設定
    auto bgColor = LayerColor::create(Color4B(219, 189, 15, 255), visibleSize.width, visibleSize.height);
    this->addChild(bgColor);
    
    // 戻るボタン
    ui::Button *backButton = ui::Button::create("back_button.png");
    backButton->setAnchorPoint(Vec2(0,0));
    backButton->setPosition(Vec2(160, 100));
    backButton->addTouchEventListener(CC_CALLBACK_2(CreditScene::touchBackEvent, this));
    this->addChild(backButton);
    
    return true;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    戻るボタン押下時のイベント
 */
void CreditScene::touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            Scene *titleScene { TitleScene::createScene() };
            Director::getInstance()->replaceScene(titleScene);
            break;
        }
        default:
            break;
    }
}
