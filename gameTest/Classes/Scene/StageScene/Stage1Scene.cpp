//
//  Stage1Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/18.
//

#include "Stage1Scene.hpp"

#pragma mark -
#pragma mark init
/**
    シーンの作成
 */
Stage1Scene* Stage1Scene::createScene()
{
    Stage1Scene *scene = new (std::nothrow) Stage1Scene();
    if (scene && scene->init(1))
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}


/**
    ステージ情報の初期化処理
 */
void Stage1Scene::initStage()
{
    this->m_isTutorialMessage1 = false;
}


/**
    MAPの初期化処理
 */
void Stage1Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map1.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage1Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター1
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(4.0f, 23.0f), ::left, 45.0f, ::patorol_roundtrip);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
}


/**
   スコア基準値の初期化処理
*/
void Stage1Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 15;
    this->m_scoreStandard.timeScoreStandardB = 30;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 0;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    Aボタン押下時に呼び出される処理
    ステージ1ではメッセージ送り以外何もしない
 */
void Stage1Scene::touchA()
{
    // メッセージダイアログが表示されていれば、文字送りを実行する
    if (this->m_mdController->isVisibleMessageDialog()) {
        this->m_mdController->next();
    }
}


/**
    Bボタン押下時に呼び出される処理
    ステージ2では何もしない
 */
void Stage1Scene::touchB()
{
    return;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage1Scene::gameStart()
{
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartSeekMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}


/**
    敵に見つかったときの処理
 */
void Stage1Scene::enemyFoundPlayer()
{
    this->allNodeUnschedule();
    this->m_mdController->createEnemyFoundPlayerMessage();
}


/**
    コンティニューを実行
 */
void Stage1Scene::doContinue()
{
    StageSceneBase::doContinue();
    
    // コンティニュー
    Scene* StageSceneBase = this->createScene();
    TransitionFade* fade = TransitionFade::create(1.0f, StageSceneBase);
    Director::getInstance()->replaceScene(fade);
}


/**
    状況の判定
 */
void Stage1Scene::checkState()
{
    // クリア座標の判定
    if (this->m_player->worldPosition() == Vec2(4.0f, 20.0f)) {
        this->stageClear();
    }
    
    // メッセージ表示
    if (this->m_player->worldPosition() == Vec2(8.0f, 26.0f)) {
        // チュートリアルメッセージ1の表示
        this->createTutorialMessage1();
    }
    
    return;
}


#pragma mark -
#pragma mark Message
/**
    チュートリアルメッセージ1を表示する
 */
void Stage1Scene::createTutorialMessage1()
{
    if (this->m_isTutorialMessage1) {
        return;
    }
    this->m_isTutorialMessage1 = true;
    
    // キャラクターの動きを一時停止
    this->gamePause();
    this->m_uiLayer->resume();
    this->m_mdController->m_dialog->resume();
    
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「見張りが巡回しているな。」");
    messages.push_back("「隠れながら進もう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this]() {
        this->gameResume();
    });
    this->m_mdController->displayMessageDialog();
}
