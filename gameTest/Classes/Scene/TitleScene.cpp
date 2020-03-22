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
    this->m_logo->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->m_logo->setPosition(Vec2(207.0f, 418.0f));
    this->addChild(this->m_logo);

    // スタートボタン
    this->m_startButton = ui::Button::create("start_button.png");
    this->m_startButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->m_startButton->setPosition(Vec2(422.0f, 145.0f));
    this->addChild(this->m_startButton);
    this->m_startButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchStartEvent, this));
    
    // プレイヤー
    this->m_playerSprite = PlayerSprite::create("player_right1.png", Vec2(0.0f, 0.0f), ::back, 0.1f);
    this->m_playerSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->m_playerSprite->setPosition(Vec2(69.0f, 435.0f));
    this->m_playerSprite->setScale(2.0f);
    this->addChild(this->m_playerSprite);
    
    // 敵
    this->m_enemySprite = EnemySprite::create("enemy1.png", Vec2(0.0f, 0.0f), ::front, 0.1f, ::patorol_none);
    this->m_enemySprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->m_enemySprite->setPosition(Vec2(939.0f, 435.0f));
    this->m_enemySprite->setScale(2.0f);
    this->addChild(this->m_enemySprite);
    
    scheduleUpdate();
    
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
            
            // ミッションモードボタン
            this->m_menu1Button = ui::Button::create("main_menu1.png");
            this->m_menu1Button->setAnchorPoint(Vec2(0.0f, 1.0f));
            this->m_menu1Button->setPosition(Vec2(136.0f, 145.0f));
            this->addChild(this->m_menu1Button);
            this->m_menu1Button->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchMissionModeEvent, this));
            
            // 遊び方ボタン
            this->m_menu2Button = ui::Button::create("main_menu2.png");
            this->m_menu2Button->setAnchorPoint(Vec2(0.0f, 1.0f));
            this->m_menu2Button->setPosition(Vec2(648.0f, 145.0f));
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
            Sprite *howToPlay = Sprite::create("howto_pic.png");
            howToPlay->setPosition(visibleSize / 2);
            this->addChild(howToPlay);
            
            // 戻るボタン
            ui::Button *backButton = ui::Button::create("backw_button.png");
            backButton->setAnchorPoint(Vec2(0,0));
            backButton->setPosition(Vec2(50, 50));
            backButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::touchBackEvent, this));
            this->addChild(backButton);
            
            break;
        }
        default:
            break;
    }
}


/**
    戻るボタン押下時のイベント
 */
void TitleScene::touchBackEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            Scene *titleScene = TitleScene::createScene();
            Director::getInstance()->replaceScene(titleScene);
            break;
        }
        default:
            break;
    }
}


#pragma mark -
#pragma mark Update
/**
    定期処理
*/
void TitleScene::update(float delta)
{
    this->updateCharactorPosition(this->m_playerSprite);
    this->updateCharactorPosition(this->m_enemySprite);
}


/**
    キャラクター座標更新
 
    @param charactor 座標を更新するキャラクター
 */
void TitleScene::updateCharactorPosition(CharacterSprite *charactor)
{
    switch (charactor->directcion()) {
        case ::right:
            if (charactor->getPosition().x < 939.0f) {
                charactor->setPosition(Vec2(charactor->getPosition().x + 5, charactor->getPosition().y));
            } else {
                charactor->setDirectcion(::back);
            }
            break;
        case ::back:
            if (charactor->getPosition().y < 556.0f) {
                charactor->setPosition(Vec2(charactor->getPosition().x, charactor->getPosition().y + 5));
            } else {
                charactor->setDirectcion(::left);
            }
            break;
        case ::left:
            if (charactor->getPosition().x > 69.0f) {
                charactor->setPosition(Vec2(charactor->getPosition().x - 5, charactor->getPosition().y));
            } else {
                charactor->setDirectcion(::front);
            }
            break;
        case ::front:
            if (charactor->getPosition().y > 320.0f) {
                charactor->setPosition(Vec2(charactor->getPosition().x, charactor->getPosition().y - 5));
            } else {
                charactor->setDirectcion(::right);
            }
            break;
        default:
            break;
    }
}
