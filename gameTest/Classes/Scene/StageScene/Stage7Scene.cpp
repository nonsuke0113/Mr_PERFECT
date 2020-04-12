//
//  Stage7Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#include "Stage7Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage7Scene* Stage7Scene::createScene()
{
    Stage7Scene *scene = new (std::nothrow) Stage7Scene();
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
void Stage7Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map7.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage7Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(6.0f, 25.0f), ::right, 0.1f, patorol_roundtrip);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(10.0f, 25.0f), ::left, 0.1f, patorol_roundtrip);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(8.0f, 26.0f), ::left, 0.1f, patorol_rotatehitwall);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy3->setRotateDirectcion(turn_right);
    this->addChild(enemy3);
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage7Scene::gameStart()
{
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartReachMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}


/**
    コンティニューを実行
 */
void Stage7Scene::doContinue()
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
void Stage7Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 20.0f)) {
        this->stageClear();
    }
    
    return;
}


/**
    ステージクリア時の処理
 */
void Stage7Scene::stageClear()
{ 
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
    
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("score7", this->m_resultInfo.timeScore + this->m_resultInfo.hpScore + this->m_resultInfo.foundScore);
}


/**
    リザルトを設定する
 */
void Stage7Scene::setupResult()
{
    // timeRank設定
    int time = (int)this->m_time / 60;
    if (time < 10) {
        this->m_resultInfo.timeScore = 3000;
    } else if (time < 20) {
        this->m_resultInfo.timeScore = 2000;
    } else {
        this->m_resultInfo.timeScore = 1000;
    }
    
    // foundRank設定
    if (this->m_enemyFoundPlayerCount == 0) {
        this->m_resultInfo.foundScore = 3000;
    } else if (this->m_enemyFoundPlayerCount <= 2) {
        this->m_resultInfo.foundScore = 2000;
    } else {
        this->m_resultInfo.foundScore = 1000;
    }
    
    this->m_resultInfo.clearStage = 7;
    
    // 親のリザルト設定処理を呼び出す
    StageSceneBase::setupResult();
}
