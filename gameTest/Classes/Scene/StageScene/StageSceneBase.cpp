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
#include "SelectMissonScene.hpp"

// 十字ボタンタグ
enum crossKeyTag {
    TAG_UP = 10,
    TAG_RIGHT = 20,
    TAG_DOWN = 30,
    TAG_LEFT = 40
};


#pragma mark -
#pragma mark init
/**
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
    this->initStart();
    
    // 操作キャラクター座標ラベル(デバッグ用)
    this->m_playerMapPointLabel = Label::createWithSystemFont(StringUtils::format("x : $%f, y : $%f", this->m_player->worldPosition().x, this->m_player->worldPosition().y), "ariel", 20);
    this->m_playerMapPointLabel->setAnchorPoint(Vec2(0,0));
    this->m_playerMapPointLabel->setPosition(Vec2(0.0f, 0.0f));
    this->m_playerMapPointLabel->setColor(Color3B(255, 0, 0));
    this->m_playerMapPointLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_playerMapPointLabel);
    
    // クリア判定をスケジュール
    schedule(schedule_selector(StageSceneBase::checkClear), 0.1f);
    
    // 座標更新をスケジュール
    schedule(schedule_selector(StageSceneBase::updatePosition), 0.1f);
    
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
    // 左サイドバー
    Sprite *leftBgSprite { Sprite::create("side.png") };
    leftBgSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    leftBgSprite->setPosition(Vec2(0.0f, 0.0f));
    leftBgSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(leftBgSprite);
    
    // 右サイドバー
    Sprite *rightBgSprite { Sprite::create("side.png") };
    rightBgSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    rightBgSprite->setPosition(Vec2(888.0f, 0.0f));
    rightBgSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(rightBgSprite);
    
    // 上ボタン
    ui::Button *upButton { ui::Button::create("up_test.png") };
    upButton->setTag(TAG_UP);
    upButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    upButton->setPosition(Vec2(60.0f, 340.0f));
    upButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(upButton);
    upButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchCrossKeyEvent, this));
    
    // 右ボタン
    ui::Button *rightButton { ui::Button::create("right_test.png") };
    rightButton->setTag(TAG_RIGHT);
    rightButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    rightButton->setPosition(Vec2(100.0f, 300.0f));
    rightButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(rightButton);
    rightButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchCrossKeyEvent, this));
    
    // 下ボタン
    ui::Button *downButton { ui::Button::create("down_test.png") };
    downButton->setTag(TAG_DOWN);
    downButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    downButton->setPosition(Vec2(60.0f, 250.0f));
    downButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(downButton);
    downButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchCrossKeyEvent, this));
    
    // 左ボタン
    ui::Button *leftButton { ui::Button::create("left_test.png") };
    leftButton->setTag(TAG_LEFT);
    leftButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    leftButton->setPosition(Vec2(10.0f, 300.0f));
    leftButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(leftButton);
    leftButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchCrossKeyEvent, this));
    
    // 十字ボタンの状態を初期化
    this->m_isPushedButton = pushedButtonNone;
    
    // Aボタン
    ui::Button *aButton { ui::Button::create("a_test.png") };
    aButton->setPosition(Vec2(880.0f, 320.0f));
    aButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(aButton);
    aButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchAEvent, this));
    
    // Aボタン2【仮】
    ui::Button *aButton2 { ui::Button::create("a_test.png") };
    aButton2->setPosition(Vec2(880.0f, 220.0f));
    aButton2->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(aButton2);
    aButton2->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchA2Event, this));
    
    // SAVEボタン【仮】
    ui::Button* saveButton { ui::Button::create("CloseNormal.png") };
    saveButton->setPosition(Vec2(880.0f, 600.0f));
    saveButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(saveButton);
    saveButton->addTouchEventListener(CC_CALLBACK_2(StageSceneBase::touchSaveEvent, this));
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
    スタート表示の初期化処理
 */
void StageSceneBase::initStart()
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
    
    return;
}


#pragma mark -
#pragma mark Getter
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
    十字キー押下時のイベント
 */
void StageSceneBase::touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // タグから押下されたボタンの方向を取得
    ui::Button* button = (ui::Button*)pSender;
    int buttonType = button->getTag();
    
    // 操作キャラクターの向きとボタンの状態を設定
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            switch (buttonType) {
                case TAG_UP:
                    this->m_player->setDirectcion(back);
                    this->m_isPushedButton = isPushedUpButton;
                    break;
                case TAG_RIGHT:
                    if(this->m_messageDialog  != nullptr && this->m_messageDialog->isYesNo) {
                        this->m_messageDialog->selectChoice(false);
                    } else {
                        this->m_player->setDirectcion(right);
                        this->m_isPushedButton = isPushedRightButton;
                    }
                    break;
                case TAG_DOWN:
                    this->m_player->setDirectcion(front);
                    this->m_isPushedButton = isPushedDownButton;
                    break;
                case TAG_LEFT:
                    if(this->m_messageDialog  != nullptr && this->m_messageDialog->isYesNo) {
                        this->m_messageDialog->selectChoice(true);
                    } else {
                        this->m_player->setDirectcion(left);
                        this->m_isPushedButton = isPushedLeftButton;
                    }
                    break;
                default:
                    break;
            }
            break;
            
        case ui::Widget::TouchEventType::MOVED:
            break;
            
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            this->m_isPushedButton = pushedButtonNone;
            break;
            
        default:
            break;
    }
}


/**
    Aボタン押下時のイベント
 */
void StageSceneBase::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            
            if(this->m_messageDialog  != nullptr &&
               this->m_messageDialog->isYesNo) {
                switch (this->m_messageDialog->m_messageType) {
                    case messageType::save:
                        if (this->m_messageDialog->userChoice) {
                            doSave();
                        }
                        break;
                    case messageType::findPlayer:
                        if (this->m_messageDialog->userChoice) {
                            doContinue();
                        } else {
                            gameover();
                        }
                        break;
                    default:
                        break;
                }
            }
            
            if (this->m_messageDialog  == nullptr) {
                // Messageテスト
                if (this->m_player->nextTileGID() != -1) {
                    this->createMessageDialog(messageType::nomal);
                }
                // 壁叩きテスト
                else {
                    //                    std::vector<Vec2> routeStack;
                    //                    std::vector<Vec2> shortestRouteStack;
                    //                    this->enemysVector().at(0)->searchShortestRoute(routeStack, shortestRouteStack, this->enemysVector().at(0)->worldPosition(), this->m_player->worldPosition());
                    //                    this->enemysVector().at(0)->startMoveAccordingToRouteStack(shortestRouteStack);
                    
                    this->enemysVector().at(0)->startChasePlayer();
                }
            }
            else {
                // 文字送りを実行する
                this->m_messageDialog->next();
            }
            break;
        }
            
        case ui::Widget::TouchEventType::MOVED:
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            break;
    }
}


/**
    テスト
    Aボタン2押下時のイベント
 */
void StageSceneBase::touchA2Event(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            this->m_player->shootBullet();
        }
            
        case ui::Widget::TouchEventType::MOVED:
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            break;
    }
}


/**
    Saveボタン押下時のイベント
 */
void StageSceneBase::touchSaveEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            // Messageテスト
            if (this->m_messageDialog  == nullptr) {
                this->createMessageDialog(messageType::save);
            }
            else {
                // 文字送りを実行する
                this->m_messageDialog->next();
            }
            break;
        }
            
        case ui::Widget::TouchEventType::MOVED:
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            break;
    }
}


#pragma mark -
/**
    ゲームオーバー
 */
void StageSceneBase::gameover()
{
    // タイトルに戻る
    Scene* titleGameScene { TitleScene::createScene() };
    TransitionFade* fade = TransitionFade::create(1.0f, titleGameScene);
    Director::getInstance()->replaceScene(fade);
}


/**
    セーブを実行
 */
void StageSceneBase::doSave()
{
    // 広告を表示
    AdMobHelper::launchInterstitial();
    
    // Save
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("playerName", this->m_player->getName());
}


/**
    コンティニューを実行
    子クラスにて自身のcreate関数を呼ぶ
 */
void StageSceneBase::doContinue()
{
    return;
}


#pragma mark -
#pragma mark Event
/**
    クリア条件を満たした
 */
void StageSceneBase::stageClear()
{
    // 全てのスケジュールを中止
    unscheduleAllCallbacks();
    
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
    
    // ミッション選択シーンに遷移
    actionAry.pushBack(CallFunc::create([]() {
        Scene *selectMissionScene { SelectMissonScene::createScene() };
        TransitionFade* fade = TransitionFade::create(1.0f, selectMissionScene);
        Director::getInstance()->replaceScene(fade);
    }));
    Sequence *actions { Sequence::create(actionAry) };
    complate->runAction(actions);
}


/**
    敵キャラクターがプレイヤーを発見した
 */
void StageSceneBase::enemyFindPlayer()
{
    this->createMessageDialog(messageType::findPlayer);
}


#pragma mark -
#pragma mark Message
/**
    メッセージダイアログを作成する
 */
void StageSceneBase::createMessageDialog(::messageType messageType)
{
    this->m_messageDialog = MessageDialog::create(640, 200);
    this->m_messageDialog->setAnchorPoint(Vec2(0.0f,0.0f));
    this->m_messageDialog->setPosition(Vec2(480.0f, 0.0f));
    this->m_messageDialog->m_messageType = messageType;
    
    // メッセージを追加
    switch (messageType) {
        case messageType::nomal:
            this->createMessage();
            break;
        case messageType::save:
            this->createSaveMessage();
            break;
        case messageType::findPlayer:
            this->createFindPlayerMessage();
            break;
        default:
            break;
    }
    
    // メッセージ表示後のコールバックを設定
    this->setMessageCallback();
    
    this->m_messageDialog->start();
    this->m_messageDialog->setScale(0.05f);
    this->m_messageDialog->runAction(
                                     Sequence::create(
                                                      ScaleTo::create(0.1f, 0, 1, 1),
                                                      ScaleTo::create(0.2f, 1, 1, 1),
                                                      nullptr)
                                     );
    this->m_messageDialog->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(this->m_messageDialog);
}


/**
    メッセージダイアログに設定する本文を作成する
 */
void StageSceneBase::createMessage()
{
    // メッセージの内容を設定
    CharacterSprite* nextChara = this->m_player->nextCharacter();
    // 人
    if(nextChara != nullptr) {
        // mobの動きを一時停止
        //        unschedule(schedule_selector(StageSceneBase::updateMobPosition));
        
        if(this->m_player->getName() != "") {
            this->m_messageDialog->addMessage(StringUtils::format("こんにちは、%s", this->m_player->getName().c_str()));
        } else {
            this->m_messageDialog->addMessage("はじめまして。");
            this->m_messageDialog->addMessage(StringUtils::format("私は%sです。", nextChara->getName().c_str()));
            this->m_messageDialog->addMessage("あなたの名前は?");
            this->m_messageDialog->addMessage("さようなら、*1");
        }
    }
    // 人以外
    else {
        this->m_messageDialog->addMessage("メッセージを開始します。");
        this->m_messageDialog->addMessage(StringUtils::format("タイルID:%d", this->m_player->nextTileGID()));
        this->m_messageDialog->addMessage("メッセージを終了します。");
    }
}


/**
    敵キャラクターがプレイヤーを発見した際のメッセージダイアログに設定する本文を作成する
 */
void StageSceneBase::createFindPlayerMessage()
{
    this->m_messageDialog->addMessage("「何者だ！」");
    this->m_messageDialog->addMessage("見つかってしまった...");
    this->m_messageDialog->addMessage("GAME OVER");
    this->m_messageDialog->addMessage("コンティニュー？$");
}


/**
    セーブ実行時のメッセージダイアログに設定する本文を作成する
 */
void StageSceneBase::createSaveMessage()
{
    this->m_messageDialog->addMessage("Saveしますか？$");
}


/**
    メッセージ表示後のコールバックを設定する
 */
void StageSceneBase::setMessageCallback()
{
    this->m_messageDialog->setCompleteAction([this]() {
        // 名前を保存
        if(this->m_messageDialog->answerList.size() != 0) {
            this->m_player->setName(this->m_messageDialog->answerList[0]);
        }
        // ダイアログを閉じて、Remove
        this->m_messageDialog->runAction(
                                         Sequence::create(
                                                          ScaleTo::create(0.1f, 0, 0.05f, 1),
                                                          ScaleTo::create(0.1f, 1, 0.05f, 0.05f),
                                                          RemoveSelf::create(true),
                                                          nullptr)
                                         );
        this->m_messageDialog  = nullptr;
    });
}


#pragma mark -
#pragma mark Update
/**
 */
void StageSceneBase::checkClear(float frame)
{
    return;
}


/**
    座標更新処理
 */
void StageSceneBase::updatePosition(float frame)
{
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((this->m_isPushedButton == pushedButtonNone) ||
        (this->m_map->getNumberOfRunningActions() > 0) ||
        (this->m_player->getActionByTag(::move) != nullptr) ||
        this->m_player->nextTileGID() != 0 ||
        this->m_player->nextCharacter() != nullptr) {
        return;
    }
    
    // カメラ座標更新
    this->updateCameraPosition();
    
    // プレイヤーの移動
    this->m_player->moveNextTile();
    
    // DEBUG:現在いる位置のラベルを更新
    this->m_playerMapPointLabel->setString(StringUtils::format("x : $%f, y : $%f", this->m_player->worldPosition().x, this->m_player->worldPosition().y));
    
    // 今いるタイルを判定
    TMXLayer* layer = this->m_map->getLayer("MAP");
    int tileGID = layer->getTileGIDAt(this->m_player->worldPosition());
    CCLOG("タイルID:%d", tileGID-1);
    CCLOG("player X:%f Y:%f", this->m_player->getPositionX(), this->m_player->getPositionY());
    CCLOG("camera X:%f Y:%f", this->m_camera->getPositionX(), this->m_camera->getPositionY());
}


/**
 カメラ座標更新
 */
void StageSceneBase::updateCameraPosition()
{
    // カメラ座標
    Vec3 newCameraPosition = this->m_camera->getPosition3D();
    
    // 上ボタン押下中
    if ((this->m_isPushedButton == isPushedUpButton) &&
        (newCameraPosition.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT / 2)) &&
        (newCameraPosition.y == this->m_player->getPosition().y))
    {
        newCameraPosition.y += PER_TILE_SIZE;
    }
    // 右ボタン押下中
    else if ((this->m_isPushedButton == isPushedRightButton)
             && (newCameraPosition.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH - PER_TILE_SIZE/2)
             // 56 = VIEW_WIDTH/2 - 基準となるx座標
             && (newCameraPosition.x == this->m_player->getPosition().x + 56))
    {
        newCameraPosition.x += PER_TILE_SIZE;
    }
    // 下ボタン押下中
    else if ((this->m_isPushedButton == isPushedDownButton) &&
             (newCameraPosition.y != VIEW_HEGHT / 2) &&
             (newCameraPosition.y == this->m_player->getPosition().y))
    {
        newCameraPosition.y -= PER_TILE_SIZE;
    }
    // 左ボタン押下中
    else if ((this->m_isPushedButton == isPushedLeftButton)
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
