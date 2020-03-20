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
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
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
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター1
    EnemySprite* mob = EnemySprite::create("enemy1.png", Vec2(4.0f, 23.0f), ::left, 0.1f, ::patorol_lookback);
    mob->setName(StringUtils::format("mob"));
    mob->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(mob);
    mob->startPatrol();
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
    this->m_isTutorialMessage1 = false;
    
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
    座標の判定
 */
void Stage1Scene::checkPosition()
{
    // クリア判定
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


/**
    ステージクリア時の処理
 */
void Stage1Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission1", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}


/**
    リザルトを設定する
 */
void Stage1Scene::setupResult()
{
    // timeRank設定
    int time = (int)this->m_time / 60;
    if (time < 10) {
        this->m_resultInfo.timeRank = ::clearRank::A;
    } else if (time < 20) {
        this->m_resultInfo.timeRank = ::clearRank::B;
    } else {
        this->m_resultInfo.timeRank = ::clearRank::C;
    }
    
    // foundRank設定
    if (this->m_enemyFoundPlayerCount == 0) {
        this->m_resultInfo.foundRank = ::clearRank::A;
    } else if (this->m_enemyFoundPlayerCount <= 2) {
        this->m_resultInfo.foundRank = ::clearRank::B;
    } else {
        this->m_resultInfo.foundRank = ::clearRank::C;
    }
    
    // 親のリザルト設定処理を呼び出す
    StageSceneBase::setupResult();
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
    
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「見張りが巡回しているな。」");
    messages.push_back("「隠れながら進もう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this](){
    });
    this->m_mdController->displayMessageDialog();
}
