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
    Label *label1 = Label::createWithTTF(StringUtils::format("CREATED BY"), "fonts/PixelMplus12-Regular.ttf", 40);
    label1->setAnchorPoint(Vec2(0.0f, 1.0f));
    label1->setPosition(Vec2(100.0f, 540.0f));
    label1->setColor(Color3B(0, 0, 0));
    this->addChild(label1);
    
    Label *label2 = Label::createWithTTF(StringUtils::format("nonsuke"), "fonts/PixelMplus12-Regular.ttf", 30);
    label2->setAnchorPoint(Vec2(0.0f, 1.0f));
    label2->setPosition(Vec2(140.0f, 480.0f));
    label2->setColor(Color3B(0, 0, 0));
    this->addChild(label2);
    
    Label *label3 = Label::createWithTTF(StringUtils::format("SPECIAL THANKS"), "fonts/PixelMplus12-Regular.ttf", 40);
    label3->setAnchorPoint(Vec2(0.0f, 1.0f));
    label3->setPosition(Vec2(568.0f, 540.0f));
    label3->setColor(Color3B(0, 0, 0));
    this->addChild(label3);
    
    Label *label4 = Label::createWithTTF(StringUtils::format("D"), "fonts/PixelMplus12-Regular.ttf", 30);
    label4->setAnchorPoint(Vec2(0.0f, 1.0f));
    label4->setPosition(Vec2(611.0f, 477.0f));
    label4->setColor(Color3B(0, 0, 0));
    this->addChild(label4);
    
    Label *label5 = Label::createWithTTF(StringUtils::format("しろ"), "fonts/PixelMplus12-Regular.ttf", 30);
    label5->setAnchorPoint(Vec2(0.0f, 1.0f));
    label5->setPosition(Vec2(608.0f, 440.0f));
    label5->setColor(Color3B(0, 0, 0));
    this->addChild(label5);

    Label *label6 = Label::createWithTTF(StringUtils::format("ちよ"), "fonts/PixelMplus12-Regular.ttf", 30);
    label6->setAnchorPoint(Vec2(0.0f, 1.0f));
    label6->setPosition(Vec2(608.0f, 400.0f));
    label6->setColor(Color3B(0, 0, 0));
    this->addChild(label6);

    Label *label7 = Label::createWithTTF(StringUtils::format("もが"), "fonts/PixelMplus12-Regular.ttf", 30);
    label7->setAnchorPoint(Vec2(0.0f, 1.0f));
    label7->setPosition(Vec2(608.0f, 360.0f));
    label7->setColor(Color3B(0, 0, 0));
    this->addChild(label7);
    
    Label *label8 = Label::createWithTTF(StringUtils::format("BGM・SE"), "fonts/PixelMplus12-Regular.ttf", 40);
    label8->setAnchorPoint(Vec2(0.0f, 1.0f));
    label8->setPosition(Vec2(100.0f, 400.0f));
    label8->setColor(Color3B(0, 0, 0));
    this->addChild(label8);
    
    Label *bgmLabel1 = Label::createWithTTF(StringUtils::format("ADDMUSIC"), "fonts/PixelMplus12-Regular.ttf", 30);
    bgmLabel1->setAnchorPoint(Vec2(0.0f, 1.0f));
    bgmLabel1->setPosition(Vec2(140.0f, 340.0f));
    bgmLabel1->setColor(Color3B(0, 0, 0));
    this->addChild(bgmLabel1);
    
    Label *bgmLabel2 = Label::createWithTTF(StringUtils::format("hitoshi by Senses Circuit"), "fonts/PixelMplus12-Regular.ttf", 30);
    bgmLabel2->setColor(Color3B(0, 0, 0));
    MenuItemLabel *menuLabel1 = MenuItemLabel::create(bgmLabel2, [](Ref * label) {
        ShareLauncher::openURL("https://www.senses-circuit.com");
    });
    menuLabel1->setAnchorPoint(Vec2(0.0f, 1.0f));
    menuLabel1->setPosition(Vec2(140.0f, 300.0f));
    Menu *menu1 = Menu::create(menuLabel1, NULL);
    menu1->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(menu1);
    
    Label *bgmLabel3 = Label::createWithTTF(StringUtils::format("On-Jin ～音人～"), "fonts/PixelMplus12-Regular.ttf", 30);
    bgmLabel3->setColor(Color3B(0, 0, 0));
    MenuItemLabel *menuLabel2 = MenuItemLabel::create(bgmLabel3, [](Ref * label) {
        ShareLauncher::openURL("https://on-jin.com/");
    });
    menuLabel2->setAnchorPoint(Vec2(0.0f, 1.0f));
    menuLabel2->setPosition(Vec2(140.0f, 260.0f));
    Menu *menu2 = Menu::create(menuLabel2, NULL);
    menu2->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(menu2);
    
    // 戻るボタン
    ui::Button *backButton = ui::Button::create("back_button.png");
    backButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    backButton->setPosition(Vec2(100.0f, 100.0f));
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
