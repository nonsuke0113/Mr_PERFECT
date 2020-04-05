//
//  CreditScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/05.
//

#include "CreditScene.hpp"
#include "TitleScene.hpp"
#include "ShareLauncher.h"

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
    
    // ラベル
    Label *bgmLabel1 = Label::createWithTTF(StringUtils::format("BGM：ADDMUSIC"), "fonts/PixelMplus12-Regular.ttf", 30);
    bgmLabel1->setAnchorPoint(Vec2(0.0f, 0.0f));
    bgmLabel1->setPosition(Vec2(160.0f, 540.0f));
    bgmLabel1->setColor(Color3B(0, 0, 0));
    this->addChild(bgmLabel1);
    
    Label *bgmLabel2 = Label::createWithTTF(StringUtils::format("BGM：hitoshi by Senses Circuit"), "fonts/PixelMplus12-Regular.ttf", 30);
    bgmLabel2->setColor(Color3B(0, 0, 0));
    MenuItemLabel *menuLabel = MenuItemLabel::create(bgmLabel2, [](Ref * label) {
        ShareLauncher::openURL("https://www.senses-circuit.com");
    });
    menuLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    menuLabel->setPosition(Vec2(160.0f, 500.0f));
    Menu *menu = Menu::create(menuLabel, NULL);
    menu->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(menu);
    
    // 戻るボタン
    ui::Button *backButton = ui::Button::create("back_button.png");
    backButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    backButton->setPosition(Vec2(160.0f, 100.0f));
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
