//
//  Stage18Scene.cpp
//  Mr.PERFECT-mobile
//
//  Created by 丹野健介 on 2020/05/03.
//

#include "Stage18Scene.hpp"
#include <AudioEngine.h>
#include "BulletSprite.hpp"

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
    // スイッチ
    this->m_switch1 = GameSpriteBase::create("switch_wall.png", Vec2(3.0f, 23.0f), ::front, false);
    this->m_switch1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_switch1);
    
    this->m_switch2 = GameSpriteBase::create("switch_wall.png", Vec2(13.0f, 23.0f), ::front, false);
    this->m_switch2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_switch2);
    
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(8.0f, 26.0f), ::left, 35.0f, ::patorol_rotateifpossible);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    enemy1->setRotateDirectcion(::turn_left);
    this->addChild(enemy1);
    
    EnemySprite* enemy2 = EnemySprite::create("enemy1.png", Vec2(6.0f, 24.0f), ::left, 35.0f, ::patorol_nomove);
    enemy2->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy2);
    
    EnemySprite* enemy3 = EnemySprite::create("enemy1.png", Vec2(10.0f, 24.0f), ::right, 35.0f, ::patorol_nomove);
    enemy3->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy3);
    
    EnemySprite* enemy4 = EnemySprite::create("enemy1.png", Vec2(8.0f, 19.0f), ::front, 25.0f, ::patorol_random);
    enemy4->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy4);
    
    // 壁
    this->m_wall = GameSpriteBase::create("wall.png", Vec2(8.0f, 23.0f), ::front, false);
    this->m_wall->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_wall);
}


/**
   スコア基準値の初期化処理
*/
void Stage18Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 45;
    this->m_scoreStandard.timeScoreStandardB = 60;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage18Scene::gameStart()
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
    // クリア判定
    if (this->enemysVector().size() == 0) {
        this->stageClear();
    }
    
    return;
}

#pragma mark -
#pragma mark ButtonEvent
/**
    Aボタン押下時に呼び出される処理
 */
void Stage18Scene::touchA()
{
    // スイッチ押下
    if ((this->m_player->worldPosition() == Vec2(3.0f, 24.0f)) &&
        (this->m_player->directcion() == ::back) &&
        this->m_switch1 != nullptr)
    {
        this->m_switch1->removeFromParent();
        this->m_switch1 = nullptr;
        
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
    }
    if ((this->m_player->worldPosition() == Vec2(13.0f, 24.0f)) &&
        (this->m_player->directcion() == ::back) &&
        this->m_switch2 != nullptr)
    {
        this->m_switch2->removeFromParent();
        this->m_switch2 = nullptr;
        
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
    }
    
    // スイッチが2つとも押されていたら、壁を消す
    if (this->m_switch1 == nullptr &&
        this->m_switch2 == nullptr &&
        this->m_wall != nullptr)
    {
        this->m_wall->removeFromParent();
        this->m_wall = nullptr;
    }
    
    // 親の処理を呼ぶ
    StageSceneBase::touchA();
}
