//
//  Stage14Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/22.
//

#include "Stage14Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage14Scene* Stage14Scene::createScene()
{
    Stage14Scene *scene = new (std::nothrow) Stage14Scene();
    if (scene && scene->init(14))
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}


/**
    キャラクターの初期化処理
 */
void Stage14Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(10.0f, 26.0f), ::front, 30.0f, patorol_roundtrip);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(10.0f, 24.0f), ::right, 30.0f, patorol_rotatehitwall);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy2->setRotateDirectcion(turn_right);
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(10.0f, 28.0f), ::left, 30.0f, patorol_rotatehitwall);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy3->setRotateDirectcion(turn_right);
    this->addChild(enemy3);
}


/**
   スコア基準値の初期化処理
*/
void Stage14Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 10;
    this->m_scoreStandard.timeScoreStandardA = 20;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage14Scene::gameStart()
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
void Stage14Scene::doContinue()
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
void Stage14Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(12.0f, 22.0f)) {
        this->stageClear();
    }
    
    return;
}
