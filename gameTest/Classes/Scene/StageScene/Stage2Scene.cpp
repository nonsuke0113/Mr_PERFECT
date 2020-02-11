//
//  Stage2Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/09.
//

#include "Stage2Scene.hpp";

#pragma mark -
#pragma mark init
/**
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
    UserDefault* userDefault = UserDefault::getInstance();
    
    // プレイヤー
    this->m_player = PlayerSprite::create("player.png", Vec2(7.0f, 16.0f), ::back, 0.1f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_player->setName(userDefault->getStringForKey("playerName"));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* mob = EnemySprite::create("enemy1.png", Vec2(7.0f, 19.0f), ::left, 0.1f);
    mob->setName(StringUtils::format("mob"));
    mob->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(mob);
    mob->startPatrol();
}

#pragma mark -
/**
 コンティニューを実行
 */
void Stage2Scene::doContinue()
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
void Stage2Scene::checkClear(float frame)
{
    if (this->m_player->worldPosition() == Vec2(7.0f, 0.0f)) {
        
        UserDefault* userDefault = UserDefault::getInstance();
        userDefault->setStringForKey("mission2", "clear");
        
        StageSceneBase::stageClear();
    }
    return;
}
