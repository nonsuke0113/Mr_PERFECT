//
//  Stage13Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#include "Stage13Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage13Scene* Stage13Scene::createScene()
{
    Stage13Scene *scene = new (std::nothrow) Stage13Scene();
    if (scene && scene->init(13))
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
void Stage13Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(5.0f, 21.0f), ::front, 45.0f, patorol_random);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(11.0f, 21.0f), ::front, 45.0f, patorol_random);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
}


/**
   スコア基準値の初期化処理
*/
void Stage13Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 60;
    this->m_scoreStandard.timeScoreStandardB = 130;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage13Scene::gameStart()
{
    // ミッション開始のメッセージ表示後、ゲームスタート
    this->m_mdController->createStartKillMissonMessage([this]() {
        StageSceneBase::gameStart();
        this->m_mdController->m_dialog->setCompleteAction(nullptr);
    });
}


/**
    コンティニューを実行
 */
void Stage13Scene::doContinue()
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
void Stage13Scene::checkState()
{
    // クリア判定
    if (this->enemysVector().size() == 0) {
        this->stageClear();
    }
    
    return;
}
