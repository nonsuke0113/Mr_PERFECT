//
//  Stage20Scene.cpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#include "Stage20Scene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage20Scene* Stage20Scene::createScene()
{
    Stage20Scene *scene = new (std::nothrow) Stage20Scene();
    if (scene && scene->init(20))
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
void Stage20Scene::initCharactors()
{
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(8.0f, 19.0f), ::right, 35.0f, patorol_rotateifpossible);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    enemy1->setRotateDirectcion(::turn_right);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(8.0f, 22.0f), ::left, 30.0f, patorol_roundtrip);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(8.0f, 24.0f), ::front, 40.0f, patorol_random);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy3);
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(5.0f, 24.0f), ::left, 30.0f, patorol_rotateifpossible);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy4);
    enemy4->setRotateDirectcion(::turn_left);
    
    EnemySprite* enemy5 = EnemySprite::create("enemy1.png", Vec2(11.0f, 24.0f), ::right, 30.0f, patorol_rotateifpossible);
    enemy5->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy5);
    enemy5->setRotateDirectcion(::turn_right);
}


/**
   スコア基準値の初期化処理
*/
void Stage20Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 15;
    this->m_scoreStandard.timeScoreStandardB = 30;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage20Scene::gameStart()
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
void Stage20Scene::doContinue()
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
void Stage20Scene::checkState()
{
    // クリア座標判定
    if (this->m_player->worldPosition() == Vec2(8.0f, 19.0f)) {
        this->stageClear();
    }
    
    return;
}
