//
//  StageSceneBase.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2019/12/17.
//

#include "StageSceneBase.hpp"
#include "Const.hpp"
#include "TitleScene.hpp"
#include "ui/UIScale9Sprite.h"
#include <typeinfo>
#include "AStarUtils.hpp"
#include "ResultScene.hpp"

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
    
    this->m_mdController = MessageDialogController::create();
    this->m_mdController->retain();
    this->addChild(this->m_mdController->m_dialog);
    
    this->m_time = 0.0f;
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
    this->touchA();
}


/**
    Aボタン押下時に呼び出される処理
    子クラスにて必要に応じて呼び出す
 */
void StageSceneBase::touchA()
{
    if (!this->m_mdController->isVisibleMessageDialog()) {
        // Messageテスト
        int nextTileGID = this->m_player->nextTileGID();
        if (nextTileGID != 1) {
            this->m_mdController->createTestMessage(nextTileGID);
        }
        // 壁叩き
        else {
            Vector<EnemySprite*> enemies = this->enemysVector();
            for (int i = 0; i < enemies.size(); i++) {
                // 遠い箇所の音は移動しない
                if (AStarUtils::calculateECost(this->m_player->worldPosition(), enemies.at(i)->worldPosition()) > 5.0) {
                    continue;
                }
                enemies.at(i)->moveToPos(this->m_player->worldPosition());
            }
        }
    }
    else {
        // 文字送りを実行する
        this->m_mdController->next();
    }
}


/**
    Bボタン押下時に呼び出される処理
    子クラスにて必要に応じて呼び出す
 */
void StageSceneBase::touchBEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    this->touchB();
}


/**
    Bボタン押下時のイベント
 */
void StageSceneBase::touchB()
{
    this->m_player->shootBullet();
    
    Vector<EnemySprite*> enemies = this->enemysVector();
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i)->moveToPos(this->m_player->worldPosition());
    }
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
    
    // 更新処理をスケジュール
    this->scheduleUpdate();
}


/**
    ゲームを一時停止する
 */
void StageSceneBase::gamePause()
{
    for (Node *node : this->enemysVector()) {
        node->pause();
    }
}


/**
    ゲームを再開する
 */
void StageSceneBase::gameResume()
{
    for (Node *node : this->enemysVector()) {
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
    // 広告を表示
    AdMobHelper::launchInterstitial();
    return;
}


/**
    クリア条件を満たした
 */
void StageSceneBase::stageClear()
{
    // 全てのスケジュールを中止
    this->allNodeUnschedule();
    
    // コンプリート表示処理
    Sprite *complate { Sprite::create("mission_complate.png") };
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    complate->setPosition(Vec2(0.0f, visibleSize.height/2));
    complate->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(complate);
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/2)));
    actionAry.pushBack(MoveTo::create(0.5f, Vec2(visibleSize.width + complate->getContentSize().width, visibleSize.height/2)));
    actionAry.pushBack(Hide::create());
    
    // リザルトの設定
    this->setupResult();
    
    // リザルトシーンに遷移
    actionAry.pushBack(CallFunc::create([this]() {
        Scene *resultScene = ResultScene::createScene(&this->m_resultInfo);
        TransitionFade* fade = TransitionFade::create(1.0f, resultScene);
        Director::getInstance()->replaceScene(fade);
    }));
    Sequence *actions = Sequence::create(actionAry);
    complate->runAction(actions);
}


/**
    リザルトを設定する
    timeRankとfoundRankは子クラスにて設定する
 */
void StageSceneBase::setupResult()
{
    this->m_resultInfo.clearTime = (int)this->m_time / 60;
    this->m_resultInfo.clearHp = this->m_player->hp();
    this->m_resultInfo.clearFoundCount = this->m_enemyFoundPlayerCount;
    this->m_resultInfo.hpRank = (::clearRank)(3 - this->m_player->hp());
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
    this->checkPosition();
    
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
    this->m_time++;
    this->m_uiLayer->updateTime(this->m_time / 30.0f);
}

/**
    座標の判定
    子クラスにて実装する
 */
void StageSceneBase::checkPosition()
{
    return;
}


/**
    座標更新処理
 */
void StageSceneBase::updatePosition()
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
    
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((padState == padNone) ||
        (this->m_mdController->isVisibleMessageDialog()) ||
        (this->m_map->getNumberOfRunningActions() > 0) ||
        (this->m_player->getActionByTag(::move) != nullptr) ||
        (!((this->m_player->nextTileGID() == 0) || (this->m_player->nextTileGID() == 3))) ||
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
             // 56 = VIEW_WIDTH/2 - 基準となるx座標
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
