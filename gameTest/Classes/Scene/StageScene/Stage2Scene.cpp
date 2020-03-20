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
    this->m_player = PlayerSprite::create("player.png", Vec2(7.0f, 16.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* mob = EnemySprite::create("enemy1.png", Vec2(7.0f, 19.0f), ::left, 0.1f, patorol_rotate);
    mob->setName(StringUtils::format("mob"));
    mob->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(mob);
//    mob->startPatrol();
}


#pragma mark -
#pragma mark GameEvent
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
    座標の判定
 */
void Stage2Scene::checkPosition()
{
    if (this->m_player->worldPosition() == Vec2(7.0f, 0.0f)) {
        this->stageClear();
    }
    return;
}


/**
    ステージクリア時の処理
 */
void Stage2Scene::stageClear()
{
    // クリア情報を保存
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("mission2", "clear");
    
    // 親のクリア処理を呼び出す
    StageSceneBase::stageClear();
}
