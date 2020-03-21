//
//  Stage3Scene.cpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2020/03/21.
//

#include "Stage3Scene.hpp"

#pragma mark -
#pragma mark Init
/**
　　 シーンの作成
 */
Stage3Scene* Stage3Scene::createScene()
{
    Stage3Scene *scene = new (std::nothrow) Stage3Scene();
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
void Stage3Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map3.tmx");
    this->addChild(this->m_map);
}


/**
　　 キャラクターの初期化処理
 */
void Stage3Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(6.0f, 23.0f), ::left, 0.1f, patorol_rotate);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(10.0f,24.0f), ::front, 0.1f, patorol_rotate);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
}


#pragma mark -
#pragma mark Message
/**
   初めてBボタンを押した時
 */
void Stage3Scene::touchB()
{
    StageSceneBase::touchB();
    this->firstshootMessage();
}


/**
    始めて銃を撃った時のメッセージを表示する
 */
void Stage3Scene::firstshootMessage()
{
    if (this->m_isfirstShootMessage) {
        return;
    }
    this->m_isfirstShootMessage = true;
    
    // キャラクターの動きを一時停止
    this->gamePause();
    this->m_uiLayer->resume();
    this->m_mdController->m_dialog->resume();
    
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「音で全ての敵に気づかれたようだ。」");
    messages.push_back("「一度隠れてやりすごそう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this](){
        this->gameResume();
    });
    this->m_mdController->displayMessageDialog();
}


#pragma mark -
#pragma mark GameEvent
/**
　　 ゲーム開始時の処理
 */
void Stage3Scene::gameStart()
{
    this->m_isTutorialMessage3 = false;
    
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartKillMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}


/**
    コンティニューを実行
 */
void Stage3Scene::doContinue()
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
void Stage3Scene::checkPosition()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 20.0f)) {
        this->stageClear();
    }
    
    // メッセージ表示
    if (this->m_player->worldPosition() == Vec2(8.0f, 26.0f)) {
        // チュートリアルメッセージ3の表示
         this->createTutorialMessage3();
    }
    
    return;
}


/**
   ステージクリア時の処理
 */
void Stage3Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission3", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}


#pragma mark -
#pragma mark Message
/**
   チュートリアルメッセージ3を表示する
 */
void Stage3Scene::createTutorialMessage3()
{
    if (this->m_isTutorialMessage3) {
        return;
    }
    this->m_isTutorialMessage3 = true;
    
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「油断している敵は一撃で倒せそうだ。」");
    messages.push_back("「Bボタンの銃弾で、後ろから敵を倒そう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this](){
    });
    this->m_mdController->displayMessageDialog();
}
