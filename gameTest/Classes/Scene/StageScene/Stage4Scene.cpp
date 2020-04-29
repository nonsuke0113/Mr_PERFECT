//
//  Stage4Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/21.
//

#include "Stage4Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage4Scene* Stage4Scene::createScene()
{
    Stage4Scene *scene = new (std::nothrow) Stage4Scene();
    if (scene && scene->init(4))
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
void Stage4Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map4.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage4Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(9.0f, 25.0f), ::left, 30.0f, patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(7.0f, 24.0f), ::right, 30.0f, patorol_nomove);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(9.0f, 23.0f), ::left, 30.0f, patorol_nomove);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy3);
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(11.0f, 15.0f), ::left, 30.0f, patorol_nomove);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy4);
}


/**
   スコア基準値の初期化処理
*/
void Stage4Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 20;
    this->m_scoreStandard.timeScoreStandardA = 40;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage4Scene::gameStart()
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
void Stage4Scene::doContinue()
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
void Stage4Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(9.0f, 14.0f)) {
        this->stageClear();
    }
    
    return;
}
