//
//  Stage16Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/20.
//

#include "Stage16Scene.hpp"
#include <AudioEngine.h>

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage16Scene* Stage16Scene::createScene()
{
    Stage16Scene *scene = new (std::nothrow) Stage16Scene();
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
void Stage16Scene::initStage()
{
    this->m_stageNum = 16;
}


/**
    MAPの初期化処理
 */
void Stage16Scene::initMap()
{
    this->m_map = TMXTiledMap::create("map16.tmx");
    this->addChild(this->m_map);
}


/**
    キャラクターの初期化処理
 */
void Stage16Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(4.0f, 25.0f), ::right, 30.0f, ::patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(12.0f, 25.0f), ::left, 30.0f, ::patorol_nomove);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    // ターゲット
    this->m_target1 = ReactsHitSprite::create("switch.png", Vec2(8.0f, 22.0f), ::front, [this]() {
        this->hitTarget1();
    });
    this->m_target1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_target1);
    
    // 壁
    this->m_wall = GameSpriteBase::create("wall.png", Vec2(8.0f, 20.0f), ::front);
    this->m_wall->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_wall);
}


/**
   スコア基準値の初期化処理
*/
void Stage16Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 60;
    this->m_scoreStandard.timeScoreStandardB = 160;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage16Scene::gameStart()
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
void Stage16Scene::doContinue()
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
void Stage16Scene::checkState()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 20.0f)) {
        this->stageClear();
    }
    
    return;
}


/**
    ターゲットに弾丸を当てた際に呼び出される処理
 */
void Stage16Scene::hitTarget1()
{
    // 出口を隠している壁を消す
    if (this->m_wall != nullptr) {
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
        this->m_wall->removeFromParent();
        this->m_wall = nullptr;
    }
}
