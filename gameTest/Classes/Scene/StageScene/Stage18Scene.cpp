//
//  Stage18Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#include "Stage18Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage18Scene* Stage18Scene::createScene()
{
    Stage18Scene *scene = new (std::nothrow) Stage18Scene();
    if (scene && scene->init(18))
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
void Stage18Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 24.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(13.0f, 29.0f), ::back, 31.0f, patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
}


/**
   スコア基準値の初期化処理
*/
void Stage18Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 20;
    this->m_scoreStandard.timeScoreStandardB = 30;
    this->m_scoreStandard.foundScoreStandardA = 10;
    this->m_scoreStandard.foundScoreStandardB = 20;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage18Scene::gameStart()
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
void Stage18Scene::doContinue()
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
void Stage18Scene::checkState()
{
    Vector<EnemySprite*> enemys = this->enemysVector();
    // 敵キャラクター追跡開始
    if (this->m_player->worldPosition() == Vec2(13.0f, 24.0f) &&
        enemys.size() != 0) {
        enemys.at(0)->setPatorolType(::patorol_chaseForever);
    }
    
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(13.0f, 0.0f)) {
        this->stageClear();
    }
    
    return;
}
