//
//  Stage2Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/09.
//

#include "Stage2Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage2Scene* Stage2Scene::createScene()
{
    Stage2Scene *scene = new (std::nothrow) Stage2Scene();
    if (scene && scene->init(2))
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
void Stage2Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map2.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage2Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(8.0f, 22.0f), ::front, 30.0f, patorol_nomove);
    enemy1->setName(StringUtils::format("mob"));
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
}


/**
   スコア基準値の初期化処理
*/
void Stage2Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 15;
    this->m_scoreStandard.timeScoreStandardB = 30;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 0;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    Bボタン押下時に呼び出される処理
    ステージ2では何もしない
 */
void Stage2Scene::touchB()
{
    return;
}



#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage2Scene::gameStart()
{
    this->m_isTutorialMessage2 = false;
    
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartSeekMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}


/**
    敵に見つかったときの処理
 */

void Stage2Scene::enemyFoundPlayer()
{
    this->allNodeUnschedule();
    this->m_mdController->createEnemyFoundPlayerMessage();
}


/**
    コンティニューを実行
 */
void Stage2Scene::doContinue()
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
void Stage2Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 20.0f)) {
        this->stageClear();
    }
    
    // メッセージ表示
    if (this->m_player->worldPosition() == Vec2(8.0f, 26.0f)) {
        // チュートリアルメッセージ2の表示
        this->createTutorialMessage2();
    }
    
    return;
}


#pragma mark -
#pragma mark Message
/**
    チュートリアルメッセージ2を表示する
 */
void Stage2Scene::createTutorialMessage2()
{
    if (this->m_isTutorialMessage2) {
        return;
    }
    this->m_isTutorialMessage2 = true;
    
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「敵が道を塞いでいるな。」");
    messages.push_back("「Aボタンで壁を叩いて、音で敵をひきつけよう。」");
    this->m_mdController->setMessages(messages);
    this->m_mdController->setMessageCallback([this](){
    });
    this->m_mdController->displayMessageDialog();
}
