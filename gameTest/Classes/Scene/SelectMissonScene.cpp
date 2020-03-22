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
#include "Stage3Scene.hpp"
#include "Stage4Scene.hpp"
#include "Stage5Scene.hpp"
#include "Stage6Scene.hpp"
#include "Stage7Scene.hpp"
#include "Stage8Scene.hpp"
#include "Stage9Scene.hpp"
#include "Stage10Scene.hpp"

#pragma mark -
#pragma mark Init
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
//            missionButton->setVisible(false);
        }
    }
    
    for (int i = 5; i < 10; i++) {
        ui::Button *missionButton = ui::Button::create(StringUtils::format("mission%s.png", std::to_string(i+1).c_str()));
        missionButton->setTag(i+1);
        missionButton->setAnchorPoint(Vec2(0,0));
        missionButton->setPosition(Vec2(568, 480 - (70 * (i - 5))));
        missionButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchMissionEvent, this));
        this->addChild(missionButton);
        
        UserDefault *userDefault = UserDefault::getInstance();
        std::string key = StringUtils::format("mission%s", std::to_string(i).c_str());
        std::string clear = userDefault->getStringForKey(key.c_str());
        if (i != 0 && clear.empty()) {
            //            missionButton->setVisible(false);
        }
    }
    
    return true;
}
    

#pragma mark -
#pragma mark ButtonEvent
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
            Scene * stageScene = nullptr;
            switch (button->getTag()) {
                case 1:
                {
                    stageScene = Stage1Scene::createScene();
                    break;
                }
                case 2:
                {
                    stageScene = Stage2Scene::createScene();
                    break;
                }
                case 3:
                {
                    stageScene = Stage3Scene::createScene();
                    break;
                }
                case 4:
                {
                    stageScene = Stage4Scene::createScene();
                    break;
                }
                case 5:
                {
                    stageScene = Stage5Scene::createScene();
                    break;
                }
                case 6:
                {
                    stageScene = Stage6Scene::createScene();
                    break;
                }
                case 7:
                {
                    stageScene = Stage7Scene::createScene();
                    break;
                }
                case 8:
                {
                    stageScene = Stage8Scene::createScene();
                    break;
                }
                case 9:
                {
                    stageScene = Stage9Scene::createScene();
                    break;
                }
                case 10:
                {
                    stageScene = Stage10Scene::createScene();
                    break;
                }
                default:
                    break;
            }
            TransitionFade* fade = TransitionFade::create(1.0f, stageScene);
            Director::getInstance()->replaceScene(fade);
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
