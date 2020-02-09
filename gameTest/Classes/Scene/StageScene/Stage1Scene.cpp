//
//  Stage1Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/18.
//

#include "Stage1Scene.hpp"

#pragma mark -
#pragma mark init
/**
 */
Stage1Scene* Stage1Scene::createScene()
{
    Stage1Scene *scene = new (std::nothrow) Stage1Scene();
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
void Stage1Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map1.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage1Scene::initCharactors()
{
    UserDefault* userDefault = UserDefault::getInstance();
    
    // プレイヤー
    this->m_player = PlayerSprite::create("player.png", Vec2(7.0f, 19.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_player->setName(userDefault->getStringForKey("playerName"));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* mob = EnemySprite::create("enemy1.png", Vec2(8.0f, 11.0f), ::left, 0.1f);
    mob->setName(StringUtils::format("mob"));
    mob->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(mob);
    mob->startPatrol();
}

#pragma mark -
/**
    コンティニューを実行
 */
void Stage1Scene::doContinue()
{
    // 広告を表示
    AdMobHelper::launchInterstitial();
    
    // コンティニュー
    Scene* StageSceneBase = this->createScene();
    TransitionFade* fade = TransitionFade::create(1.0f, StageSceneBase);
    Director::getInstance()->replaceScene(fade);
}


#pragma mark -
/**
 */
void Stage1Scene::checkClear(float frame)
{
    if (this->m_player->worldPosition() == Vec2(7.0f, 0.0f)) {
        
        UserDefault* userDefault = UserDefault::getInstance();
        userDefault->setStringForKey("mission1", "clear");
        
        StageSceneBase::stageClear();
    }
    return;
}

