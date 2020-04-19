//
//  Stage8Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#include "Stage8Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage8Scene* Stage8Scene::createScene()
{
    Stage8Scene *scene = new (std::nothrow) Stage8Scene();
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
void Stage8Scene::initStage()
{
    this->m_stageNum = 8;
}


/**
    MAPの初期化処理
 */
void Stage8Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map8.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage8Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(11.0f, 26.0f), ::left, 0.1f, patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
}


/**
   スコア基準値の初期化処理
*/
void Stage8Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 30;
    this->m_scoreStandard.timeScoreStandardA = 45;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 1;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage8Scene::gameStart()
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
void Stage8Scene::doContinue()
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
void Stage8Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(10.0f, 24.0f)) {
        this->stageClear();
    }
    
    return;
}
