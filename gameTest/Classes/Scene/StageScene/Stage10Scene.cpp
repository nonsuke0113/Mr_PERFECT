//
//  Stage10Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#include "Stage10Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage10Scene* Stage10Scene::createScene()
{
    Stage10Scene *scene = new (std::nothrow) Stage10Scene();
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
void Stage10Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map10.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage10Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(6.0f, 26.0f), ::front, 0.1f, patorol_lookback);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    enemy1->startPatrol();
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(10.0f, 26.0f), ::back, 0.1f, patorol_lookback);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    enemy2->startPatrol();
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(8.0f, 26.0f), ::left, 0.1f, patorol_rotate);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy3->setRotateDirectcion(turn_right);
    this->addChild(enemy3);
    enemy3->startPatrol();
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(8.0f, 24.0f), ::right, 0.1f, patorol_lookback);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy4);
    enemy4->startPatrol();
    
    EnemySprite* enemy5 = EnemySprite::create("enemy1.png", Vec2(8.0f, 22.0f), ::left, 0.1f, patorol_lookback);
    enemy5->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy5);
    enemy5->startPatrol();
    
    EnemySprite* enemy6 = EnemySprite::create("enemy1.png", Vec2(6.0f, 22.0f), ::front, 0.1f, patorol_lookback);
    enemy6->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy6);
    enemy6->startPatrol();
    
    EnemySprite* enemy7 = EnemySprite::create("enemy1.png", Vec2(10.0f, 21.0f), ::back, 0.1f, patorol_lookback);
    enemy7->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy7);
    enemy7->startPatrol();
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage10Scene::gameStart()
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
void Stage10Scene::doContinue()
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
void Stage10Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 18.0f)) {
        this->stageClear();
    }
    
    return;
}


/**
    ステージクリア時の処理
 */
void Stage10Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission10", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}
