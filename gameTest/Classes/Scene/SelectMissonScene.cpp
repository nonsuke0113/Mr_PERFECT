//
//  SelectMissonScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/01/31.
//

#include "SelectMissonScene.hpp"
#include "TitleScene.hpp"
#include "StageSceneBase.hpp"
#include <AudioEngine.h>
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
#include "Stage11Scene.hpp"
#include "Stage12Scene.hpp"
#include "Stage13Scene.hpp"
#include "Stage14Scene.hpp"
#include "Stage15Scene.hpp"
#include "Stage16Scene.hpp"

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
    
    // ページ設定
    this->m_page = 1;
    
    // 進むボタン
    this->m_nextButton = ui::Button::create("back_button.png");
    this->m_nextButton->setAnchorPoint(Vec2(1.0f, 0.0f));
    this->m_nextButton->setPosition(Vec2(1036.0f, 100.0f));
    this->m_nextButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchNextEvent, this));
    this->addChild(this->m_nextButton);
    
    // 戻るボタン
    this->m_backButton = ui::Button::create("back_button.png");
    this->m_backButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_backButton->setPosition(Vec2(100.0f, 100.0f));
    this->m_backButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchBackEvent, this));
    this->addChild(this->m_backButton);
    
    //
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 5; k++) {
                // ミッションボタン
                ui::Button *missionButton = ui::Button::create(StringUtils::format("mission%s.png", std::to_string(k + 1 + (j * 5) + (i * 10)).c_str()));
                missionButton->setTag(k + 1 + (j * 5) + (i * 10));
                missionButton->setAnchorPoint(Vec2(0.0f, 1.0f));
                missionButton->setPosition(Vec2(100.0f + (j * 516.0f), 540.0f - (75.0f * k)));
                missionButton->addTouchEventListener(CC_CALLBACK_2(SelectMissonScene::touchMissionEvent, this));
                missionButton->setVisible(false);
                this->addChild(missionButton);
                this->m_missionButtons.pushBack(missionButton);
                
                // スコアラベル
                Label *scoreLabel = Label::createWithTTF(StringUtils::format("%05d", 12000).c_str(), "fonts/PixelMplus12-Regular.ttf", 30);
                scoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
                scoreLabel->setPosition(Vec2(385.0f + (j * 516.0f), (540.0f - (75.0f * k) - 5.0f)));
                scoreLabel->setColor(Color3B(0, 0, 0));
                scoreLabel->setVisible(false);
                this->addChild(scoreLabel);
                this->m_scoreLabels.pushBack(scoreLabel);
                
                // ランク画像
                Sprite *rankSprite = Sprite::create("rank_P.png");
                rankSprite->setScale(0.5f);
                rankSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
                rankSprite->setPosition(Vec2(480.0f + (j * 516.0f), 540.0f - (75.0f * k)));
                rankSprite->setVisible(false);
                this->addChild(rankSprite);
                this->m_rankSprites.pushBack(rankSprite);
            }
        }
    }
    
    this->updateView();
    return true;
}


#pragma mark -
#pragma mark Update
/**
    表示内容の更新
 */
void SelectMissonScene::updateView()
{
    // 進むボタンの表示
    UserDefault *userDefault = UserDefault::getInstance();
    if (this->m_page == 1 && userDefault->getIntegerForKey("score10") != 0) {
        this->m_nextButton->setVisible(true);
    } else {
        this->m_nextButton->setVisible(false);
    }
    
    for (int i = 0; i < 20; i++) {
        
        if ((i < ((this->m_page - 1) * 10)) ||
            (i >= (this->m_page * 10)))
        {
            this->m_missionButtons.at(i)->setVisible(false);
            this->m_scoreLabels.at(i)->setVisible(false);
            this->m_rankSprites.at(i)->setVisible(false);
            continue;
        }
        
        // ページごと初期表示
        if (i == (this->m_page - 1) * 10) {
            this->m_missionButtons.at(i)->setVisible(true);
        }
        
        // クリア情報の確認
        std::string key = StringUtils::format("score%s", std::to_string(i + 1).c_str());
        int score = userDefault->getIntegerForKey(key.c_str());
        
        // 表示
        if (score != 0) {
            this->m_missionButtons.at(i + 1)->setVisible(true);
            Label *scoreLabel = this->m_scoreLabels.at(i);
            scoreLabel->setString(StringUtils::format("%05d", score).c_str());
            scoreLabel->setVisible(true);
            Sprite *rankSprite = this->m_rankSprites.at(i);
            if (score < TOTAL_SCORE_P_STANDARD && score >= TOTAL_SCORE_A_STANDARD) {
                rankSprite->setTexture("rank_A.png");
            } else if (score < TOTAL_SCORE_A_STANDARD && score >= TOTAL_SCORE_B_STANDARD) {
                rankSprite->setTexture("rank_B.png");
            } else if (score < TOTAL_SCORE_B_STANDARD) {
                rankSprite->setTexture("rank_C.png");
            }
            rankSprite->setVisible(true);
        }
    }
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
                case 11:
                {
                    stageScene = Stage11Scene::createScene();
                    break;
                }
                case 12:
                {
                    stageScene = Stage12Scene::createScene();
                    break;
                }
                case 13:
                {
                    stageScene = Stage13Scene::createScene();
                    break;
                }
                case 14:
                {
                    stageScene = Stage14Scene::createScene();
                    break;
                }
                case 15:
                {
                    stageScene = Stage15Scene::createScene();
                    break;
                }
                case 16:
                {
                    stageScene = Stage16Scene::createScene();
                    break;
                }
                default:
                    break;
            }
            
            // BGMを停止
            experimental::AudioEngine::stopAll();
            
            TransitionFade* fade = TransitionFade::create(1.0f, stageScene);
            Director::getInstance()->replaceScene(fade);
            break;
        }
        default:
            break;
    }
}


/**
    進むボタン押下時のイベント
 */
void SelectMissonScene::touchNextEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            this->m_page++;
            this->updateView();
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
            if (this->m_page == 1) {
                Scene *titleScene = TitleScene::createScene();
                Director::getInstance()->replaceScene(titleScene);
            } else {
                this->m_page--;
                this->updateView();
            }
            break;
        }
        default:
            break;
    }
}
