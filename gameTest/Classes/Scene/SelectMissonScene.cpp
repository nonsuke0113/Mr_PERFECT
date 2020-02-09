//
//  SelectMissonScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/01/31.
//

#include "SelectMissonScene.hpp"
#include "TitleScene.hpp"
#include "StageSceneBase.hpp"
#include "Stage1Scene.hpp"
#include "Stage2Scene.hpp"

/**
    シーンの作成
 */
Scene* SelectMissonScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectMissonScene::create();
    scene->addChild(layer);
    return scene;
}


/**
    初期化処理
 */
bool SelectMissonScene::init()
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
    backButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchBackEvent, this));
    this->addChild(backButton);
    
    // ミッションボタン
    for (int i = 0; i < 5; i++) {
        ui::Button *missionButton = ui::Button::create(StringUtils::format("mission%s.png", std::to_string(i+1).c_str()));
        missionButton->setTag(i+1);
        missionButton->setAnchorPoint(Vec2(0,0));
        missionButton->setPosition(Vec2(160, 480 - (70 * i)));
        missionButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchMissionEvent, this));
        this->addChild(missionButton);
        
        UserDefault *userDefault = UserDefault::getInstance();
        std::string key = StringUtils::format("mission%s", std::to_string(i).c_str());
        std::string clear = userDefault->getStringForKey(key.c_str());
        if (i != 0 && clear.empty()) {
            missionButton->setVisible(false);
        }
    }
    
    return true;
}
    

/**
    ミッションボタン押下時のイベント
 */
void SelectMissonScene::touchMissionEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            ui::Button *button = (ui::Button*)pSender;
            switch (button->getTag()) {
                case 1:
                {
                    Scene *stage1Scene { Stage1Scene::createScene() };
                    TransitionFade* fade = TransitionFade::create(1.0f, stage1Scene);
                    Director::getInstance()->replaceScene(fade);
                    break;
                }
                case 2:
                {
                    Scene *stage1Scene { Stage2Scene::createScene() };
                    TransitionFade* fade = TransitionFade::create(1.0f, stage1Scene);
                    Director::getInstance()->replaceScene(fade);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}


/**
    戻るボタン押下時のイベント
 */
void SelectMissonScene::touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type)
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
