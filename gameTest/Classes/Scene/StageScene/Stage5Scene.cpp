//
//  Stage5Scene.cpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2020/03/21.
//

#include "Stage5Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage5Scene* Stage5Scene::createScene()
{
    Stage5Scene *scene = new (std::nothrow) Stage5Scene();
    if (scene && scene->init(5))
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
void Stage5Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(8.0f, 23.0f), ::right, 30.0f, patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(9.0f, 24.0f), ::left, 30.0f, patorol_nomove);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(12.0f, 25.0f), ::left, 30.0f, patorol_nomove);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy3);
}


/**
   スコア基準値の初期化処理
*/
void Stage5Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 45;
    this->m_scoreStandard.timeScoreStandardB = 60;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    コンティニューを実行
 */
void Stage5Scene::doContinue()
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
void Stage5Scene::checkState()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(13.0f, 24.0f)) {
        this->stageClear();
    }
    
    return;
}


/**
    ゲーム開始時の処理
 */
void Stage5Scene::gameStart()
{
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartReachMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}

