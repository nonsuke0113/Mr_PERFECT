//
//  Stage19Scene.cpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#include "Stage19Scene.hpp"
#include <AudioEngine.h>
#include "BulletSprite.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage19Scene* Stage19Scene::createScene()
{
    Stage19Scene *scene = new (std::nothrow) Stage19Scene();
    if (scene && scene->init(19))
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
void Stage19Scene::initCharactors()
{
    // スイッチ
    this->m_switch1 = GameSpriteBase::create("switch_wall.png", Vec2(7.0f, 20.0f), ::front, false);
    this->m_switch1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_switch1);
    
    this->m_switch2 = GameSpriteBase::create("switch_wall.png", Vec2(16.0f, 20.0f), ::front, false);
    this->m_switch2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_switch2);
    
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(6.0f, 18.0f), ::right, 25.0f, ::patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(11.0f, 18.0f), ::right, 25.0f, ::patorol_rotateifpossible);
    enemy2->setRotateDirectcion(::turn_right);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(16.0f, 18.0f), ::left, 25.0f, ::patorol_nomove);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy3);
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(14.0f, 25.0f), ::left, 30.0f, ::patorol_rotateifpossible);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy4->setRotateDirectcion(::turn_right);
    this->addChild(enemy4);
    
    // 壁
    this->m_wall1 = GameSpriteBase::create("wall.png", Vec2(8.0f, 21.0f), ::front, false);
    this->m_wall1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_wall1);
    
    this->m_wall2 = GameSpriteBase::create("wall.png", Vec2(11.0f, 21.0f), ::front, false);
    this->m_wall2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_wall2);
}


/**
   スコア基準値の初期化処理
*/
void Stage19Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 60;
    this->m_scoreStandard.timeScoreStandardB = 190;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage19Scene::gameStart()
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
void Stage19Scene::doContinue()
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
void Stage19Scene::checkState()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(11.0f, 17.0f)) {
        this->stageClear();
    }
    
    return;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    Aボタン押下時に呼び出される処理
 */
void Stage19Scene::touchA()
{
    // スイッチ押下
    if ((this->m_player->worldPosition() == Vec2(7.0f, 21.0f)) &&
        (this->m_player->directcion() == ::back) &&
        this->m_switch1 != nullptr)
    {
        this->m_switch1->removeFromParent();
        this->m_switch1 = nullptr;
        
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
        
        this->m_wall1->removeFromParent();
        this->m_wall1 = nullptr;
        return;
    }
    if ((this->m_player->worldPosition() == Vec2(16.0f, 21.0f)) &&
        (this->m_player->directcion() == ::back) &&
        this->m_switch2 != nullptr)
    {
        this->m_switch2->removeFromParent();
        this->m_switch2 = nullptr;
        
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
        
        this->m_wall2->removeFromParent();
        this->m_wall2 = nullptr;
        return;
    }

    // 親の処理を呼ぶ
    StageSceneBase::touchA();
}
