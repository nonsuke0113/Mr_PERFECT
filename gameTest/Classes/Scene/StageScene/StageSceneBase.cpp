//
//  StageSceneBase.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/17.
//

#include "StageSceneBase.hpp"
#include "TitleScene.hpp"
#include "ui/UIScale9Sprite.h"
#include <typeinfo>
#include "AStarUtils.hpp"
#include "ResultScene.hpp"
#include "SelectMissonScene.hpp"
#include <AudioEngine.h>

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 */
StageSceneBase* StageSceneBase::createScene()
{
    StageSceneBase *scene = new (std::nothrow) StageSceneBase();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}


/**
    初期化処理
 */
bool StageSceneBase::init()
{
    if (!Scene::init()) {
        return false;
    }
    this->initCamera();
    this->initUI();
    this->initMap();
    this->initCharactors();
    this->initScoreStandard();
    
    this->m_mdController = MessageDialogController::create();
    this->m_mdController->retain();
    this->addChild(this->m_mdController->m_dialog);
    
    this->m_time = 0.0f;
    this->m_shootBulletInterval = 0.0f;
    this->m_enemyFoundPlayerCount = 0;
    
    this->gameStart();
    
    return true;
}


/**
    固定用カメラの初期化処理
 */
void StageSceneBase::initCamera()
{
    this->m_camera = this->getDefaultCamera();
    this->m_camera->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    // 固定用カメラを追加
    Camera *camera1 = Camera::create();
    camera1->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera1);
}


/**
    UIの初期化処理
 */
void StageSceneBase::initUI()
{
    // UIレイヤーを追加
    this->m_uiLayer = StageUILayer::create();
    this->m_uiLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(this->m_uiLayer);
}


/**
    MAPの初期化処理
    子クラスにて実装する
 */
void StageSceneBase::initMap()
{
    return;
}


/**
    キャラクターの初期化処理
    子クラスにて実装する
 */
void StageSceneBase::initCharactors()
{
    return;
}


/**
    スコア基準値の初期化処理
    子クラスにて実装する
 */
void StageSceneBase::initScoreStandard()
{
    return;
}


#pragma mark -
#pragma mark Getter
/**
    バーチャルパッドの状態を返却する

    @return バーチャルパッドの向き
 */
::padState StageSceneBase::padState()
{
    return this->m_uiLayer->padState();
}


/**
    キャラクターの一覧を返す
 
    @return キャラクターの一覧
 */
Vector<CharacterSprite*> StageSceneBase::charactersVector() {
    Vector<Node*> nodes = this->getChildren();
    Vector<CharacterSprite*> characters;
    for (int i = 0; i < nodes.size(); i++) {
        if (typeid(*nodes.at(i)) == typeid(PlayerSprite) ||
            typeid(*nodes.at(i)) == typeid(EnemySprite)){
            characters.pushBack((CharacterSprite*)nodes.at(i));
        }
    }
    return characters;
}


/**
    敵キャラクターの一覧を返す
 
    @return 敵キャラクターの一覧を返す
 */
Vector<EnemySprite*> StageSceneBase::enemysVector() {
    Vector<Node*> nodes = this->getChildren();
    Vector<EnemySprite*> enemysVector;
    for (int i = 0; i < nodes.size(); i++) {
        if (typeid(*nodes.at(i)) == typeid(EnemySprite)) {
            enemysVector.pushBack((EnemySprite*)nodes.at(i));
        }
    }
    return enemysVector;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    Aボタン押下時のイベント
 */
void StageSceneBase::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // ゲーム終了時は何もしない
    if (this->m_state == GameState::End) {
        return;
    }
    this->touchA();
}


/**
    Aボタン押下時に呼び出される処理
    子クラスにて必要に応じて呼び出す
 */
void StageSceneBase::touchA()
{
    // メッセージダイアログ表示中であれば、文字送りをして終了
    if (this->m_mdController->isVisibleMessageDialog()) {
        // 文字送りを実行する
        this->m_mdController->next();
        return;
    }
    
    // 壁叩き
    int nextTileGID = this->m_player->nextTileGID();
    if (isWallTileGID(nextTileGID)) {
        this->playerKnockWall();
    }
}


/**
    プレイヤーが壁を叩いた
 */
void StageSceneBase::playerKnockWall()
{
    this->m_player->knockWall();
    
    // SE再生
    experimental::AudioEngine::play2d("_sound_various_mp3_door-iron-knock1.mp3", false);
    
    Vector<EnemySprite*> enemies = this->enemysVector();
    for (int i = 0; i < enemies.size(); i++) {
        // 遠い箇所の音は移動しない
        if (AStarUtils::calculateECost(this->m_player->worldPosition(), enemies.at(i)->worldPosition()) > enemies.at(i)->hearableRange()) {
            continue;
            
        }
        enemies.at(i)->showSpeechBubble(::exclamation);
        enemies.at(i)->moveToPos(this->m_player->worldPosition());
    }
}


/**
    Bボタン押下時に呼び出される処理
    子クラスにて必要に応じて呼び出す
 */
void StageSceneBase::touchBEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // ゲーム進行中以外は何もしない
    if (this->m_state != GameState::InProgress) {
        return;
    }
    this->touchB();
}


/**
    Bボタン押下時のイベント
 */
void StageSceneBase::touchB()
{
    // メッセージダイアログ表示中であれば何もしない
    if (this->m_mdController->isVisibleMessageDialog()) {
        return;
    }
    
    // 1秒以内は撃てない
    if (this->m_shootBulletInterval <= SHOOT_BULLET_INTERVAL) {
        return;
    }
    this->m_shootBulletInterval = 0.0f;
    
    this->m_player->shootBullet();
    
    Vector<EnemySprite*> enemies = this->enemysVector();
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i)->showSpeechBubble(::exclamation);
        enemies.at(i)->moveToPos(this->m_player->worldPosition());
    }
}


/**
    一時停止ボタン押下時のイベント
 */
void StageSceneBase::touchPauseEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // ゲーム進行中以外、またはすでにメッセージ表示中であれば何もしない
    if ((this->m_state != GameState::InProgress) ||
        (this->m_mdController->m_dialog->isVisible())) {
        return;
    }
    // 中断する
    this->gamePause();
    this->m_uiLayer->resume();
    this->m_mdController->m_dialog->resume();
    this->m_mdController->createPauseMessage();
}


#pragma mark -
/**
    ゲームを開始する処理
 */
void StageSceneBase::gameStart()
{
    Sprite *start { Sprite::create("mission_start.png") };
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    start->setPosition(Vec2(0.0f, visibleSize.height/2));
    this->addChild(start);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(0.5f, Vec2(visibleSize.width + start->getContentSize().width, visibleSize.height/2)));
    actionAry.pushBack(Hide::create());
    Sequence *actions { Sequence::create(actionAry) };
    start->runAction(actions);
    
    // BGMを停止
    experimental::AudioEngine::stopAll();
    // BGMを開始
    experimental::AudioEngine::play2d("0017_Spy-Mission.mp3", true);
    
    // 更新処理をスケジュール
    this->scheduleUpdate();
    for (EnemySprite *enemy : this->enemysVector()) {
        enemy->startPatrol();
    }
    
    this->m_state = GameState::InProgress;
}


/**
    ゲームを一時停止する
 */
void StageSceneBase::gamePause()
{
    this->m_state = GameState::Pause;
    for (Node *node : this->getChildren()) {
        node->pause();
    }
}


/**
    ゲームを再開する
 */
void StageSceneBase::gameResume()
{
    this->m_state = GameState::InProgress;
    for (Node *node : this->getChildren()) {
        node->resume();
    }
}


/**
    自身と子のスケジュールを全てキャンセルする
 */
void StageSceneBase::allNodeUnschedule()
{
    for (int i = 0; i < this->getChildren().size(); i++) {
        this->getChildren().at(i)->unscheduleAllCallbacks();
    }
    this->unscheduleAllCallbacks();
}


#pragma mark -
#pragma mark GameEvent
/**
    ゲームオーバー
 */
void StageSceneBase::gameover()
{
    // BGMを停止
    experimental::AudioEngine::stopAll();
    
    // 広告を表示
    AdMobHelper::launchInterstitial();
    
    // タイトルに戻る
    Scene* titleGameScene { TitleScene::createScene() };
    TransitionFade* fade = TransitionFade::create(1.0f, titleGameScene);
    Director::getInstance()->replaceScene(fade);
}


/**
    コンティニューを実行
    子クラスにて自身のcreate関数を呼ぶ
 */
void StageSceneBase::doContinue()
{
    // BGMを停止
    experimental::AudioEngine::stopAll();
    // 広告を表示
    AdMobHelper::launchInterstitial();
    return;
}


/**
    クリア条件を満たした
 */
void StageSceneBase::stageClear()
{
    // BGMを停止
    experimental::AudioEngine::stopAll();
    
    // 全てのスケジュールを中止
    this->allNodeUnschedule();
    
    // ステータス更新
    this->m_state = GameState::End;
    
    // コンプリート表示処理
    Sprite *complete { Sprite::create("mission_complete.png") };
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    complete->setPosition(Vec2(0.0f, visibleSize.height/2));
    complete->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(complete);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(0.5f, Vec2(visibleSize.width + complete->getContentSize().width, visibleSize.height/2)));
    actionAry.pushBack(Hide::create());
    
    // リザルトの設定
    this->setupResult();
    
    // リザルトシーンに遷移
    actionAry.pushBack(CallFunc::create([this]() {
        Scene *resultScene = ResultScene::createScene(this->m_resultInfo);
        TransitionFade* fade = TransitionFade::create(1.0f, resultScene);
        Director::getInstance()->replaceScene(fade);
    }));
    Sequence *actions = Sequence::create(actionAry);
    complete->runAction(actions);
    
    // SE再生
    experimental::AudioEngine::play2d("jazzjingle.mp3", false);
}


/**
    リザルトを設定する
    timeRankとfoundRankは子クラスにて設定する
 */
void StageSceneBase::setupResult()
{
    // 実際の値を設定
    this->m_resultInfo.clearTime = (int)this->m_time / 60;
    this->m_resultInfo.clearHp = this->m_player->hp();
    this->m_resultInfo.clearFoundCount = this->m_enemyFoundPlayerCount;
    
    // 値を元にスコアを計算
    // タイムスコア = ステージごとの基準値に応じて設定 + (ランク基準値 - クリアタイム) * 50のボーナス
    if (this->m_resultInfo.clearTime <= this->m_scoreStandard.timeScoreStandardA) {
        this->m_resultInfo.timeScore = SCORE_A_STANDARD_BY_ITEM;
        this->m_resultInfo.timeScore += (this->m_scoreStandard.timeScoreStandardA - this->m_resultInfo.clearTime) * TIME_SCORE_BONUS_PS;
    } else if (this->m_resultInfo.clearTime <= this->m_scoreStandard.timeScoreStandardB) {
        this->m_resultInfo.timeScore = SCORE_B_STANDARD_BY_ITEM;
        this->m_resultInfo.timeScore += (this->m_scoreStandard.timeScoreStandardB - this->m_resultInfo.clearTime) * TIME_SCORE_BONUS_PS;
    } else {
        this->m_resultInfo.timeScore = SCORE_C_STANDARD_BY_ITEM;
    }
    // HPスコア = 残HP * 1000
    this->m_resultInfo.hpScore = this->m_player->hp() * HP_SCORE_MAGNIGICATION;
    // 発見数スコア = ステージごとの基準値に応じて設定
    if (this->m_resultInfo.clearFoundCount <= this->m_scoreStandard.foundScoreStandardA) {
        this->m_resultInfo.foundScore = SCORE_A_STANDARD_BY_ITEM;
    } else if (this->m_resultInfo.clearFoundCount <= this->m_scoreStandard.foundScoreStandardB) {
        this->m_resultInfo.foundScore = SCORE_B_STANDARD_BY_ITEM;
    } else {
        this->m_resultInfo.foundScore = SCORE_C_STANDARD_BY_ITEM;
    }
}

/**
    ミッション選択シーンに戻る
 */
void StageSceneBase::backMissionSelectScene()
{
    // BGMを停止
    experimental::AudioEngine::stopAll();
    
    // 全てのスケジュールを中止
    this->allNodeUnschedule();
    
    Scene *resultScene = SelectMissonScene::createScene();
    TransitionFade* fade = TransitionFade::create(1.0f, resultScene);
    Director::getInstance()->replaceScene(fade);
}


/**
    ミッション失敗
 */
void StageSceneBase::missionFailed()
{
    // 全てのスケジュールを中止
    this->allNodeUnschedule();
    
    // 失敗表示処理
    Sprite *failed { Sprite::create("mission_failed.png") };
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    failed->setPosition(Vec2(0.0f, visibleSize.height / 2));
    failed->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(failed);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    // コンテニューメッセージダイアログを表示する
    actionAry.pushBack(CallFunc::create([this]() {
        this->m_mdController->createMissionFailedMessage();
    }));
    Sequence *actions { Sequence::create(actionAry) };
    failed->runAction(actions);
    
    // SE再生
    experimental::AudioEngine::play2d("bossyuu.mp3", false);
}


/**
    敵キャラクターがプレイヤーを発見した
 */
void StageSceneBase::enemyFoundPlayer()
{
    this->m_enemyFoundPlayerCount++;
}


/**
    プレイヤーが被弾した
 
    @param i 残りHP
 */
void StageSceneBase::heartOff(int i)
{
    this->m_uiLayer->heartOff(i);
}


#pragma mark -
#pragma mark Update
/**
    定期処理
 */
void StageSceneBase::update(float delta)
{
    this->updateTime();
    this->checkState();
    this->updatePlayerDirection();
    
    // 座標更新は0.5秒(30/60フレーム)毎に判定
    if (fmod(this->m_time, 30) == 0) {
        this->updatePosition();
    }
}


/**
    経過時間の更新
 */
void StageSceneBase::updateTime()
{
    // ゲーム進行中以外は更新しない
    if (this->m_state != GameState::InProgress) {
        return;
    }
    this->m_time++;
    this->m_uiLayer->updateTime(this->m_time / 60);
    
    this->m_shootBulletInterval++;
}


/**
    状況の判定
    子クラスにて実装する
 */
void StageSceneBase::checkState()
{
    return;
}


/**
    プレイヤーの向きを更新
 */
void StageSceneBase::updatePlayerDirection()
{
    ::padState padState = this->padState();
    switch (padState) {
        case padUp:
            this->m_player->setDirectcion(back);
            break;
        case padRight:
            this->m_player->setDirectcion(right);
            break;
        case padDown:
            this->m_player->setDirectcion(front);
            break;
        case padLeft:
            this->m_player->setDirectcion(left);
            break;
        default:
            break;
    }
}


/**
    座標更新処理
 */
void StageSceneBase::updatePosition()
{
    // ゲームパッドが真ん中だったり、行けない道だったら何もしない
    if ((this->m_state != GameState::InProgress) ||
        (this->padState() == padNone) ||
        (this->m_mdController->isVisibleMessageDialog()) ||
        (this->m_map->getNumberOfRunningActions() > 0) ||
        (this->m_player->getActionByTag(::move) != nullptr) ||
        (!(isCanEnterTileGID(this->m_player->nextTileGID()))) ||
        this->m_player->nextCharacter() != nullptr) {
        return;
    }
    
    // カメラ座標更新
    this->updateCameraPosition();
    
    // プレイヤーの移動
    this->m_player->moveNextTile();
}


/**
    カメラ座標更新
 */
void StageSceneBase::updateCameraPosition()
{
    // カメラ座標
    Vec3 newCameraPosition = this->m_camera->getPosition3D();
    
    ::padState padState = this->m_uiLayer->padState();
    
    // 上ボタン押下中
    if ((padState == padUp) &&
        (newCameraPosition.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT / 2)) &&
        (newCameraPosition.y == this->m_player->getPosition().y))
    {
        newCameraPosition.y += PER_TILE_SIZE;
    }
    // 右ボタン押下中
    else if ((padState == padRight)
             && (newCameraPosition.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH - PER_TILE_SIZE/2)
             // 56 = VIEW_WIDTH/2 - プレイヤーの初期x座標
             && (newCameraPosition.x == this->m_player->getPosition().x + 56))
    {
        newCameraPosition.x += PER_TILE_SIZE;
    }
    // 下ボタン押下中
    else if ((padState == padDown) &&
             (newCameraPosition.y != VIEW_HEGHT / 2) &&
             (newCameraPosition.y == this->m_player->getPosition().y))
    {
        newCameraPosition.y -= PER_TILE_SIZE;
    }
    // 左ボタン押下中
    else if ((padState == padLeft)
             && (newCameraPosition.x != VIEW_WIDTH / 2 - SIDE_BAR_WIDTH + PER_TILE_SIZE/2)
             && (newCameraPosition.x == this->m_player->getPosition().x + 56))
    {
        newCameraPosition.x -= PER_TILE_SIZE;
    }
    
    // カメラ移動
    MoveTo* actionMove = MoveTo::create(0.1f, newCameraPosition);
    this->m_camera->stopAllActions();
    this->m_camera->runAction(actionMove);
}
