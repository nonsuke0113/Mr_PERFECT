//
//  Stage6Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#include "Stage6Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage6Scene* Stage6Scene::createScene()
{
    Stage6Scene *scene = new (std::nothrow) Stage6Scene();
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
void Stage6Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map6.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage6Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(9.0f, 26.0f), ::left, 0.1f, patorol_rotatehitwall);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy1->setRotateDirectcion(::turn_left);
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(8.0f, 24.0f), ::back, 0.1f, patorol_roundtrip);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(12.0f, 24.0f), ::left, 0.1f, patorol_rotatehitwall);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy3->setRotateDirectcion(::turn_left);
    this->addChild(enemy3);
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(11.0f, 22.0f), ::back, 0.1f, patorol_roundtrip);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy4);
    
    EnemySprite* enemy5 = EnemySprite::create("enemy1.png", Vec2(11.0f, 28.0f), ::front, 0.1f, patorol_roundtrip);
    enemy5->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy5);
}


/**
    コンティニューを実行
 */
void Stage6Scene::doContinue()
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
void Stage6Scene::checkState()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(14.0f, 25.0f)) {
        this->stageClear();
    }
    
    return;
}


/**
    ステージクリア時の処理
 */
void Stage6Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission5", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage6Scene::gameStart()
{
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartReachMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}

