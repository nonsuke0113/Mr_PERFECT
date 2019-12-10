//
//  MainGameScene.cpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//
// AdMob Id ca-app-pub-4909093571037310~5693701652

#include "Const.hpp"
#include "TitleScene.hpp"
#include "MainGameScene.hpp"
#include "ui/UIScale9Sprite.h"

#include "AdMobHelper.h"

USING_NS_CC;

// 十字ボタンタグ
enum crossKeyTag {
    TAG_UP = 10,
    TAG_RIGHT = 20,
    TAG_DOWN = 30,
    TAG_LEFT = 40
};


/**
    シーンの作成
 */
Scene* MainGameScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    
    // 固定用カメラを追加
    layer->pCamera = scene->getDefaultCamera();
    layer->pCamera->setAnchorPoint(Vec2(0.0f, 0.0f));
    Camera* camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    layer->addChild(camera);
    
    scene->addChild(layer);
    return scene;
}


/**
    初期化処理
 */
bool MainGameScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    // UI初期化
    this->initUI();
    
    // キャラクター初期化
    this->initCharactor();
    
    // 操作キャラクター座標ラベル(デバッグ用)
    this->playerMapPointLabel = Label::createWithSystemFont(StringUtils::format("x : $%f, y : $%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y), "ariel", 20);
    this->playerMapPointLabel->setAnchorPoint(Vec2(0,0));
    this->playerMapPointLabel->setPosition(Vec2(0.0f, 0.0f));
    this->playerMapPointLabel->setColor(Color3B(255, 0, 0));
    this->playerMapPointLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(playerMapPointLabel);
    
    // 座標更新をスケジュール
    schedule(schedule_selector(MainGameScene::updatePosition), 0.1f);
    
    CCLOG("player X:%f Y:%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y);
    
    return true;
}


/**
    UIの初期化
 */
void MainGameScene::initUI() {
    
    // マップ
    this->pMap = TMXTiledMap::create("map1.tmx");
    this->addChild(this->pMap);
    
    // 左サイドバー
    Sprite* leftBgSprite { Sprite::create("side_test.png") };
    leftBgSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    leftBgSprite->setPosition(Vec2(0.0f, 0.0f));
    leftBgSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(leftBgSprite);
    
    // 右サイドバー
    Sprite* rightBgSprite { Sprite::create("side_test.png") };
    rightBgSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    rightBgSprite->setPosition(Vec2(800.0f, 0.0f));
    rightBgSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(rightBgSprite);
    
    // 上ボタン
    ui::Button* upButton { ui::Button::create("up_test.png") };
    upButton->setTag(TAG_UP);
    upButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    upButton->setPosition(Vec2(60.0f, 340.0f));
    upButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(upButton);
    upButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchCrossKeyEvent, this));
    
    // 右ボタン
    ui::Button* rightButton { ui::Button::create("right_test.png") };
    rightButton->setTag(TAG_RIGHT);
    rightButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    rightButton->setPosition(Vec2(100.0f, 300.0f));
    rightButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(rightButton);
    rightButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchCrossKeyEvent, this));
    
    // 下ボタン
    ui::Button* downButton { ui::Button::create("down_test.png") };
    downButton->setTag(TAG_DOWN);
    downButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    downButton->setPosition(Vec2(60.0f, 250.0f));
    downButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(downButton);
    downButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchCrossKeyEvent, this));
    
    // 左ボタン
    ui::Button* leftButton { ui::Button::create("left_test.png") };
    leftButton->setTag(TAG_LEFT);
    leftButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    leftButton->setPosition(Vec2(10.0f, 300.0f));
    leftButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(leftButton);
    leftButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchCrossKeyEvent, this));
    
    // 十字ボタンの状態を初期化
    this->m_isPushedButton = pushedButtonNone;
    
    // Aボタン
    ui::Button* aButton { ui::Button::create("a_test.png") };
    aButton->setPosition(Vec2(880.0f, 320.0f));
    aButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(aButton);
    aButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchAEvent, this));
    
    // Aボタン2
    ui::Button* aButton2 { ui::Button::create("a_test.png") };
    aButton2->setPosition(Vec2(880.0f, 220.0f));
    aButton2->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(aButton2);
    aButton2->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchA2Event, this));
    
    // SAVEボタン(仮)
    ui::Button* saveButton { ui::Button::create("CloseNormal.png") };
    saveButton->setPosition(Vec2(880.0f, 600.0f));
    saveButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(saveButton);
    saveButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchSaveEvent, this));
}


/**
    キャラクターの初期化
 */
void MainGameScene::initCharactor() {
    
    UserDefault* userDefault = UserDefault::getInstance();
    
    this->charactersVector = new (std::nothrow) Vector<CharacterSprite*>;
    this->enemysVector = new (std::nothrow) Vector<EnemySprite*>;
    
    // プレイヤー
    this->pPlayer = CharacterSprite::create("chara.png", Vec2(7.0f, 19.0f), this->pMap, 0.1f);
    this->pPlayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->pPlayer->setName(userDefault->getStringForKey("playerName"));
    this->addChild(this->pPlayer);
    this->charactersVector->pushBack(this->pPlayer);
    
    // 敵キャラクター
    EnemySprite* mob = EnemySprite::create("enemy.png", Vec2(8.0f, 11.0f), this->pMap, 0.1f);
    mob->setName(StringUtils::format("mob"));
    mob->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(mob);
    this->charactersVector->pushBack(mob);
    this->enemysVector->pushBack(mob);
    mob->startPatrol();
}


#pragma mark -
#pragma mark ButtonEvent
/**
    十字キー押下時のイベント
 */
void MainGameScene::touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type) {
    
    // タグから押下されたボタンの方向を取得
    ui::Button* button = (ui::Button*)pSender;
    int buttonType = button->getTag();
    
    // 操作キャラクターの向きとボタンの状態を設定
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            switch (buttonType) {
                case TAG_UP:
                    this->pPlayer->setDirectcion(back);
                    this->m_isPushedButton = isPushedUpButton;
                    break;
                case TAG_RIGHT:
                    if(this->messageDialog != nullptr && this->messageDialog->isYesNo) {
                        this->messageDialog->selectChoice(false);
                    } else {
                        this->pPlayer->setDirectcion(right);
                        this->m_isPushedButton = isPushedRightButton;
                    }
                    break;
                case TAG_DOWN:
                    this->pPlayer->setDirectcion(front);
                    this->m_isPushedButton = isPushedDownButton;
                    break;
                case TAG_LEFT:
                    if(this->messageDialog != nullptr && this->messageDialog->isYesNo) {
                        this->messageDialog->selectChoice(true);
                    } else {
                        this->pPlayer->setDirectcion(left);
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
void MainGameScene::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type) {
    
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            
            if(this->messageDialog != nullptr &&
               this->messageDialog->isYesNo) {
                switch (this->messageDialog->m_messageType) {
                    case messageType::save:
                        if (this->messageDialog->userChoice) {
                            doSave();
                        }
                        break;
                    case messageType::findPlayer:
                        if (this->messageDialog->userChoice) {
                            doContinue();
                        } else {
                            gameover();
                        }
                        break;
                    default:
                        break;
                }
            }
            
            if (this->messageDialog == nullptr) {
                // Messageテスト
                if (this->pPlayer->nextTileGID() != -1) {
                    this->createMessageDialog(messageType::nomal);
                }
                // 壁叩きテスト
                else {
                    std::vector<Vec2> routeStack;
                    std::vector<Vec2> shortestRouteStack;
                    this->enemysVector->at(0)->searchShortestRoute(routeStack, shortestRouteStack, this->enemysVector->at(0)->worldPosition(), this->pPlayer->worldPosition());
                    this->enemysVector->at(0)->startMoveAccordingToRouteStack(shortestRouteStack);
                }
            }
            else {
                // 文字送りを実行する
                this->messageDialog->next();
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
void MainGameScene::touchA2Event(Ref *pSender, ui::Widget::TouchEventType type) {
    
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            
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
void MainGameScene::touchSaveEvent(Ref *pSender, ui::Widget::TouchEventType type) {
    
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            // Messageテスト
            if (this->messageDialog == nullptr) {
                this->createMessageDialog(messageType::save);
            }
            else {
                // 文字送りを実行する
                this->messageDialog->next();
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
void MainGameScene::gameover() {
    // タイトルに戻る
    Scene* titleGameScene { TitleScene::createScene() };
    TransitionFade* fade = TransitionFade::create(1.0f, titleGameScene);
    Director::getInstance()->replaceScene(fade);
}


/**
    セーブを実行
 */
void MainGameScene::doSave() {
    // 広告を表示
    AdMobHelper::launchInterstitial();
    
    // Save
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("playerName", this->pPlayer->getName());
}


/**
    コンティニューを実行
 */
void MainGameScene::doContinue() {
    // 広告を表示
    AdMobHelper::launchInterstitial();
    
    // コンティニュー
    Scene* mainGameScene { MainGameScene::createScene() };
    TransitionFade* fade = TransitionFade::create(1.0f, mainGameScene);
    Director::getInstance()->replaceScene(fade);
}


#pragma mark -
#pragma mark Event
/**
    敵キャラクターがプレイヤーを発見した
 */
void MainGameScene::enemyFindPlayer() {
    this->createMessageDialog(messageType::findPlayer);
}


#pragma mark -
#pragma mark Message
/**
    メッセージダイアログを作成する
 */
void MainGameScene::createMessageDialog(::messageType messageType) {
    
    this->messageDialog = MessageDialog::create(640, 200);
    this->messageDialog->setAnchorPoint(Vec2(0.0f,0.0f));
    this->messageDialog->setPosition(Vec2(480.0f, 0.0f));
    this->messageDialog->m_messageType = messageType;
    
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
    
    this->messageDialog->start();
    this->messageDialog->setScale(0.05f);
    this->messageDialog->runAction(
        Sequence::create(
            ScaleTo::create(0.1f, 0, 1, 1),
            ScaleTo::create(0.2f, 1, 1, 1),
            nullptr)
    );
    this->messageDialog->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(this->messageDialog);
}


/**
    メッセージダイアログに設定する本文を作成する
 */
void MainGameScene::createMessage() {
    
    // メッセージの内容を設定
    CharacterSprite* nextChara = this->pPlayer->nextCharacter();
    // 人
    if(nextChara != nullptr) {
        // mobの動きを一時停止
//        unschedule(schedule_selector(MainGameScene::updateMobPosition));
        
        if(this->pPlayer->getName() != "") {
            this->messageDialog->addMessage(StringUtils::format("こんにちは、%s", this->pPlayer->getName().c_str()));
        } else {
            this->messageDialog->addMessage("はじめまして。");
            this->messageDialog->addMessage(StringUtils::format("私は%sです。", nextChara->getName().c_str()));
            this->messageDialog->addMessage("あなたの名前は?");
            this->messageDialog->addMessage("さようなら、*1");
        }
    }
    // 人以外
    else {
        this->messageDialog->addMessage("メッセージを開始します。");
        this->messageDialog->addMessage(StringUtils::format("タイルID:%d", this->pPlayer->nextTileGID()));
        this->messageDialog->addMessage("メッセージを終了します。");
    }
}


/**
    敵キャラクターがプレイヤーを発見した際のメッセージダイアログに設定する本文を作成する
 */
void MainGameScene::createFindPlayerMessage() {
    this->messageDialog->addMessage("「何者だ！」");
    this->messageDialog->addMessage("見つかってしまった...");
    this->messageDialog->addMessage("GAME OVER");
    this->messageDialog->addMessage("コンティニュー？$");
}


/**
    セーブ実行時のメッセージダイアログに設定する本文を作成する
 */
void MainGameScene::createSaveMessage() {
    this->messageDialog->addMessage("Saveしますか？$");
}


/**
    メッセージ表示後のコールバックを設定する
 */
void MainGameScene::setMessageCallback() {
    
    this->messageDialog->setCompleteAction([this]() {
        // 名前を保存
        if(this->messageDialog->answerList.size() != 0) {
            this->pPlayer->setName(this->messageDialog->answerList[0]);
        }
        // ダイアログを閉じて、Remove
        this->messageDialog->runAction(
                                       Sequence::create(
                                                        ScaleTo::create(0.1f, 0, 0.05f, 1),
                                                        ScaleTo::create(0.1f, 1, 0.05f, 0.05f),
                                                        RemoveSelf::create(true),
                                                        nullptr)
                                       );
        this->messageDialog = nullptr;
//        schedule(schedule_selector(MainGameScene::updateMobPosition), 2.0f);
    });
}


#pragma mark -
#pragma mark Update
/**
    座標更新処理
 */
void MainGameScene::updatePosition(float frame) {
    
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((this->m_isPushedButton == pushedButtonNone) ||
        (this->pMap->getNumberOfRunningActions() > 0) ||
        (this->pPlayer->getNumberOfRunningActions() > 0) ||
        this->pPlayer->nextTileGID() != 0 ||
        this->pPlayer->nextCharacter() != nullptr) {
        return;
    }
    
    // カメラ座標更新
    this->updateCameraPosition();
    
    // プレイヤーの移動
    this->pPlayer->moveNextTile();
    
    // DEBUG:現在いる位置のラベルを更新
    this->playerMapPointLabel->setString(StringUtils::format("x : $%f, y : $%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y));
    
    // 今いるタイルを判定
    TMXLayer* layer = this->pMap->getLayer("MAP");
    int tileGID = layer->getTileGIDAt(this->pPlayer->worldPosition());
    CCLOG("タイルID:%d", tileGID-1);
    CCLOG("player X:%f Y:%f", this->pPlayer->getPositionX(), this->pPlayer->getPositionY());
    CCLOG("camera X:%f Y:%f", this->pCamera->getPositionX(), this->pCamera->getPositionY());
}


/**
    カメラ座標更新
 */
void MainGameScene::updateCameraPosition() {
    // カメラ座標
    Vec3 newCameraPosition = this->pCamera->getPosition3D();
    
    // 上ボタン押下中
    if ((this->m_isPushedButton == isPushedUpButton) &&
        (newCameraPosition.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT / 2)) &&
        (newCameraPosition.y == this->pPlayer->getPosition().y))
    {
        newCameraPosition.y += PER_TILE_SIZE;
    }
    // 右ボタン押下中
    else if ((this->m_isPushedButton == isPushedRightButton) &&
             (newCameraPosition.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH) &&
             (newCameraPosition.x == this->pPlayer->getPosition().x))
    {
        newCameraPosition.x += PER_TILE_SIZE;
    }
    // 下ボタン押下中
    else if ((this->m_isPushedButton == isPushedDownButton) &&
             (newCameraPosition.y != VIEW_HEGHT / 2) &&
             (newCameraPosition.y == this->pPlayer->getPosition().y))
    {
        newCameraPosition.y -= PER_TILE_SIZE;
    }
    // 左ボタン押下中
    else if ((this->m_isPushedButton == isPushedLeftButton) &&
             (newCameraPosition.x != VIEW_WIDTH / 2 - SIDE_BAR_WIDTH) &&
             (newCameraPosition.x == this->pPlayer->getPosition().x))
    {
        newCameraPosition.x -= PER_TILE_SIZE;
    }
    
    // カメラ移動
    MoveTo* actionMove = MoveTo::create(0.1f, newCameraPosition);
    this->pCamera->stopAllActions();
    this->pCamera->runAction(actionMove);
}
