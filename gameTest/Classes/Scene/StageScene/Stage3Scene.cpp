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
    ステージ情報の初期化処理
 */
void Stage3Scene::initStage()
{
    this->m_stageNum = 3;
    this->m_isTutorialMessage3 = false;
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
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1_back1.png", Vec2(5.0f, 22.0f), ::right, 30.0f, patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1_left1.png", Vec2(10.0f, 22.0f), ::back, 30.0f, patorol_nomove);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
}


/**
   スコア基準値の初期化処理
*/
void Stage3Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 30;
    this->m_scoreStandard.timeScoreStandardA = 45;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
　　 ゲーム開始時の処理
 */
void Stage3Scene::gameStart()
{
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
    状況の判定
 */
void Stage3Scene::checkState()
{
    // クリア判定
    if (this->enemysVector().size() == 0) {
        this->stageClear();
    }
    
    // メッセージ表示
    if (this->m_player->worldPosition() == Vec2(8.0f, 26.0f)) {
        // チュートリアルメッセージ3の表示
         this->createTutorialMessage3();
    }
    
    return;
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
    messages.push_back("「Bボタンで銃を撃って、後ろから敵を倒そう。」");
    messages.push_back("「ただし銃声がすると全ての敵に気づかれる。」");
    messages.push_back("「撃った後は、一度隠れてやりすごそう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this](){
    });
    this->m_mdController->displayMessageDialog();
}

