//
//  Stage8Scene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/23.
//

#include "Stage8Scene.hpp"
#include <AudioEngine.h>
#include "BulletSprite.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
Stage8Scene* Stage8Scene::createScene()
{
    Stage8Scene *scene = new (std::nothrow) Stage8Scene();
    if (scene && scene->init(8))
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
void Stage8Scene::initCharactors()
{
    // 床のスイッチ
    this->m_switch1 = GameSpriteBase::create("switch_floor.png", Vec2(7.0f, 26.0f), ::front, true);
    this->m_switch1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_switch1);
    this->m_isSwitch1On = false;
    
    // プレイヤー
    this->m_player = PlayerSprite::create("player_back1.png", Vec2(8.0f, 29.0f), ::back, 30.0f);
    this->m_player->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_player);
    
    // 敵キャラクター
    EnemySprite* enemy1 = EnemySprite::create("enemy1.png", Vec2(6.0f, 29.0f), ::back, 30.0f, ::patorol_nomove);
    enemy1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(enemy1);
    
    // ターゲット
    this->m_target1 = ReactsHitSprite::create("target_wall.png", Vec2(8.0f, 22.0f), ::front, [this]() {
        this->hitTarget1();
    });
    this->m_target1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->m_target1);
}


/**
   スコア基準値の初期化処理
*/
void Stage8Scene::initScoreStandard()
{
    this->m_scoreStandard.timeScoreStandardA = 10;
    this->m_scoreStandard.timeScoreStandardB = 15;
    this->m_scoreStandard.foundScoreStandardA = 0;
    this->m_scoreStandard.foundScoreStandardB = 2;
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲーム開始時の処理
 */
void Stage8Scene::gameStart()
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
void Stage8Scene::doContinue()
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
void Stage8Scene::checkState()
{
    // クリア判定
    if (this->m_player->worldPosition() == Vec2(6.0f, 22.0f)) {
        this->stageClear();
    }
    // スイッチ判定
    if (this->m_switch1 != nullptr) {
        this->checkSwitch();
    }
    
    return;
}

/**
    
 */
void Stage8Scene::checkSwitch()
{
    bool onSwitch = false;
    for (CharacterSprite *chara : this->charactersVector()) {
        if (chara->worldPosition() == Vec2(7.0f, 26.0f)) {
            onSwitch = true;
            break;
        }
    }
    if (onSwitch && !this->m_isSwitch1On) {
        this->m_isSwitch1On = true;
        experimental::AudioEngine::play2d("handgun-firing1.mp3", false);
        BulletSprite* bullet = BulletSprite::create(Vec2(5.0f, 26.0f), ::right, nullptr, 0.1f);
        bullet->setAnchorPoint(Vec2(0.0f, 0.0f));
        this->addChild(bullet);
        bullet->shootBullet(::right);
    }
    else if (!onSwitch && this->m_isSwitch1On) {
        this->m_isSwitch1On = false;
    }
}


/**
    ターゲットに弾丸を当てた際に呼び出される処理
 */
void Stage8Scene::hitTarget1()
{
    if (this->m_switch1 != nullptr) {
        // SE再生
        experimental::AudioEngine::play2d("switch.mp3", false);
        // スイッチを削除
        this->m_switch1->removeFromParent();
        this->m_switch1 = nullptr;
    }
}
