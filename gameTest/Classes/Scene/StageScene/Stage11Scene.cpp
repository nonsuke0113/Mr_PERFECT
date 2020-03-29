//
//  Stage11Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/29.
//

#include "Stage11Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage11Scene* Stage11Scene::createScene()
{
    Stage11Scene *scene = new (std::nothrow) Stage11Scene();
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
void Stage11Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map11.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage11Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    GameSpriteBase *warp1 = GameSpriteBase::create("warp.png", Vec2(8.0f, 24.0f), ::back);
    warp1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(warp1);
    
    GameSpriteBase *warp2 = GameSpriteBase::create("warp.png", Vec2(8.0f, 21.0f), ::back);
    warp2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(warp2);
    
//    // 敵キャラクター
//    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(10.0f, 26.0f), ::front, 0.1f, patorol_roundtrip);
//    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
//    this->addChild(enemy1);
//
//    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(10.0f, 24.0f), ::right, 0.1f, patorol_rotatehitwall);
//    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
//    enemy2->setRotateDirectcion(turn_right);
//    this->addChild(enemy2);
//
//    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(10.0f, 28.0f), ::left, 0.1f, patorol_rotatehitwall);
//    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
//    enemy3->setRotateDirectcion(turn_right);
//    this->addChild(enemy3);
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage11Scene::gameStart()
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
void Stage11Scene::doContinue()
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
void Stage11Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 16.0f)) {
        this->stageClear();
    }
    
    
    
    return;
}


/**
    ワープを実行する
 */
void Stage11Scene::warpIfNeed()
{
    Vec3 newCameraPosition = this->m_camera->getPosition3D();
    MoveTo *actionMove = MoveTo::create(0.1f, newCameraPosition);
    
    if (this->m_player->worldPosition() == Vec2(8.0f, 24.0f)) {
        this->m_player->moveWorld(0.1f, Vec2(8.0f, 20.0f));
        newCameraPosition.y += PER_TILE_SIZE * 4.0f;
        actionMove = MoveTo::create(0.1f, newCameraPosition);
    }
    else if (this->m_player->worldPosition() == Vec2(8.0f, 21.0f)) {
        this->m_player->moveWorld(0.1f, Vec2(8.0f, 25.0f));
        newCameraPosition.y -= PER_TILE_SIZE * 4.0f;
        actionMove = MoveTo::create(0.1f, newCameraPosition);
    }
    
    this->m_camera->stopAllActions();
    this->m_camera->runAction(actionMove);
    return;
}


/**
    ステージクリア時の処理
 */
void Stage11Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission11", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}
