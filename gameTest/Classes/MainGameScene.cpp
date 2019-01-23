//
//  MainGameScene.cpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#include "Const.hpp"
#include "MainGameScene.hpp"

USING_NS_CC;

// 十字ボタン状態
enum pushedButton {
    pushedButtonNone,
    isPushedUpButton,
    isPushedRightButton,
    isPushedDownButton,
    isPushedLeftButton
};
pushedButton m_isPushedButton = pushedButtonNone;

// 十字ボタンタグ
enum crossKeyTag {
    TAG_UP = 10,
    TAG_RIGHT = 20,
    TAG_DOWN = 30,
    TAG_LEFT = 40
};

Scene* MainGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    
    // スクロール用カメラを追加
    layer->pCamera = scene->getDefaultCamera();
    layer->pCamera->setAnchorPoint(Vec2(0.0f, 0.0f));
    Camera* camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    layer->addChild(camera);
    
    scene->addChild(layer);
    return scene;
}


bool MainGameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    // マップ
    this->pMap = TMXTiledMap::create("desert.tmx");
//    this->pMap->runAction(ScaleTo::create(0.1f, 2, 2, 1));
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
    
    // Aボタン
    ui::Button* aButton { ui::Button::create("a_test.png") };
    aButton->setPosition(Vec2(880.0f, 320.0f));
    aButton->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(aButton);
    aButton->addTouchEventListener(CC_CALLBACK_2(MainGameScene::touchAEvent, this));
    
    // キャラクター
    this->pPlayer = CharacterSprite::create("obento.png", Vec2(15.0f, 29.0f), this->pMap);
    this->pPlayer->setAnchorPoint(Vec2(0.0f, 0.0f));
//    this->pPlayer->runAction(ScaleTo::create(0.1f, 2, 2, 1));
    this->addChild(this->pPlayer);
    this->charactersVector.push_back(this->pPlayer);
    
    // モブキャラクター
    for(int i=0; i<4; i++) {
        float random = rand()%10+1;
        float random2 = rand()%10+1;
        Vec2 pos = Vec2(random+10, random2+20);
        CharacterSprite* mob = CharacterSprite::create("bilding.png", pos, this->pMap);
        mob->setName(StringUtils::format("mob%d", i));
        mob->setAnchorPoint(Vec2(0.0f, 0.0f));
        this->addChild(mob);
        this->charactersVector.push_back(mob);
    }
    
    // Debugラベル
    this->playerMapPointLabel = Label::createWithSystemFont(StringUtils::format("x : $%f, y : $%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y), "ariel", 20);
    this->playerMapPointLabel->setAnchorPoint(Vec2(0,0));
    this->playerMapPointLabel->setPosition(Vec2(0.0f, 0.0f));
    this->playerMapPointLabel->setColor(Color3B(255, 0, 0));
    this->playerMapPointLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(playerMapPointLabel);
    
    // 座標更新をスケジュール
    schedule(schedule_selector(MainGameScene::updatePosition), 0.1f);
    schedule(schedule_selector(MainGameScene::updateMobPosition), 2.0f);
    
    CCLOG("player X:%f Y:%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y);
    
    return true;
}


/**
 十字キー押下時のイベント
 */
void MainGameScene::touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // タグから押下されたボタンの方向を取得
    ui::Button* button = (ui::Button*)pSender;
    int buttonType = button->getTag();
    
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            switch (buttonType) {
                case TAG_UP:
                    this->pPlayer->setCharacterDirectcion(character_back);
                    m_isPushedButton = isPushedUpButton;
                    break;
                case TAG_RIGHT:
                    this->pPlayer->setCharacterDirectcion(character_right);
                    m_isPushedButton = isPushedRightButton;
                    break;
                case TAG_DOWN:
                    this->pPlayer->setCharacterDirectcion(character_front);
                    m_isPushedButton = isPushedDownButton;
                    break;
                case TAG_LEFT:
                    this->pPlayer->setCharacterDirectcion(character_left);
                    m_isPushedButton = isPushedLeftButton;
                    break;
                default:
                    break;
            }
            break;
        }
            
        case ui::Widget::TouchEventType::MOVED:
            break;
            
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
        {
            m_isPushedButton = pushedButtonNone;
        }
    }
}


/**
 Aボタン押下時のイベント
 */
void MainGameScene::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type) {
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            // Messageテスト
            if (this->messageDialog == nullptr)
            {
                this->messageDialog = MessageDialog::create(640, 200);
                this->messageDialog->addMessage("メッセージを開始します。");
                CharacterSprite* nextChara = this->pPlayer->getNextCharacter();
                if(nextChara != nullptr) {
                    this->messageDialog->addMessage(StringUtils::format("人:%s", nextChara->getName().c_str()));
                } else {
                    this->messageDialog->addMessage(StringUtils::format("タイルID:%d", this->pPlayer->getNextTileGID()));
                }
                this->messageDialog->addMessage("メッセージを終了します。");
                this->messageDialog->setAnchorPoint(Vec2(0.0f,0.0f));
                this->messageDialog->setPosition(Vec2(480.0f, 0.0f));
                this->messageDialog->setCompleteAction([this]()
                {
                    this->messageDialog->runAction(
                                                   Sequence::create(
                                                                    ScaleTo::create(0.1f, 0, 0.05f, 1),
                                                                    ScaleTo::create(0.1f, 1, 0.05f, 0.05f),
                                                                    RemoveSelf::create(true),
                                                                    nullptr
                                                                    )
                                                   );
                    this->messageDialog = nullptr;
                });
                this->messageDialog->start();
                this->messageDialog->setScale(0.05f);
                this->messageDialog->runAction(
                                         Sequence::create(
                                                          ScaleTo::create(0.1f, 0, 1, 1),
                                                          ScaleTo::create(0.2f, 1, 1, 1),
                                                          nullptr
                                                          )
                );
                this->messageDialog->setCameraMask((unsigned short)CameraFlag::USER1);
                this->addChild(this->messageDialog);
            }
            else {
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
 座標更新処理
 */
void MainGameScene::updatePosition(float frame) {
    
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((m_isPushedButton == pushedButtonNone) ||
        (this->pMap->getNumberOfRunningActions() > 0) ||
        (this->pPlayer->getNumberOfRunningActions() > 0) ||
        this->pPlayer->getNextTileGID() != 29 ||
        this->pPlayer->getNextCharacter() != nullptr) {
        return;
    }
    
    // カメラ座標
    Vec3 newCameraPosition = this->pCamera->getPosition3D();
    MoveTo* actionMove;
    // キャラクター座標
    Vec2 newPlayerPosition = this->pPlayer->worldPosition();
    
    // 上ボタン押下中
    if (m_isPushedButton == isPushedUpButton) {
        if((newCameraPosition.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT/2)) &&
        (newCameraPosition.y == this->pPlayer->getPosition().y)) {
            // カメラを上へ移動
            newCameraPosition.y += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        // キャラクターを上へ移動
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x, newPlayerPosition.y-1.0f));
    }
    
    // 右ボタン押下中
    if (m_isPushedButton == isPushedRightButton) {
        if((newCameraPosition.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH) &&
           (newCameraPosition.x == this->pPlayer->getPosition().x)) {
            // カメラを右へ移動
            newCameraPosition.x += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        // キャラクターを右へ移動
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x+1.0f, newPlayerPosition.y));
    }
    
    // 下ボタン押下中
    if (m_isPushedButton == isPushedDownButton) {
        if ((newCameraPosition.y != VIEW_HEGHT/2) &&
            (newCameraPosition.y == this->pPlayer->getPosition().y)) {
            // カメラを下へ移動
            newCameraPosition.y -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        // キャラクターを下へ移動
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x, newPlayerPosition.y+1.0f));
    }
    
    // 左ボタン押下中
    if (m_isPushedButton == isPushedLeftButton) {
        if((newCameraPosition.x != VIEW_WIDTH/2 - SIDE_BAR_WIDTH) &&
           (newCameraPosition.x == this->pPlayer->getPosition().x)) {
            // カメラを左へ移動
            newCameraPosition.x -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        // キャラクターを左へ移動
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x-1.0f, newPlayerPosition.y));
    }
    
    // DEBUG:現在いる位置のラベルを更新
    this->playerMapPointLabel->setString(StringUtils::format("x : $%f, y : $%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y));
    
    // 今いるタイルを判定
    TMXLayer* layer = this->pMap->getLayer("Ground");
    int tileGID = layer->getTileGIDAt(this->pPlayer->worldPosition());
    CCLOG("タイルID:%d", tileGID-1);
    CCLOG("player X:%f Y:%f", this->pPlayer->getPositionX(), this->pPlayer->getPositionY());
    CCLOG("camera X:%f Y:%f", this->pCamera->getPositionX(), this->pCamera->getPositionY());
}

/**
 モブの座標を更新
 */
void MainGameScene::updateMobPosition(float frame) {
    
    for (int i=1; i<this->charactersVector.size(); i++) {
        
        CharacterSprite* chara = this->charactersVector[i];
        int random = rand()%4+1;
        switch(random) {
            case 1:
                chara->setCharacterDirectcion(character_back);
                break;
            case 2:
                chara->setCharacterDirectcion(character_right);
                break;
            case 3:
                chara->setCharacterDirectcion(character_front);
                break;
            case 4:
                chara->setCharacterDirectcion(character_left);
                break;
        }
        
        if (chara->getNumberOfRunningActions() > 0 ||
            chara->getNextTileGID() != 29 ||
            chara->getNextCharacter() != nullptr) {
            return;
        }
        
        Vec2 newCharaPoint = chara->worldPosition();
        
        if(random == 1) {
            chara->moveWorld(0.1f, Vec2(newCharaPoint.x, newCharaPoint.y-1.0f));
        } else if(random == 2) {
            chara->moveWorld(0.1f, Vec2(newCharaPoint.x+1.0f, newCharaPoint.y));
        } else if(random == 3) {
            chara->moveWorld(0.1f, Vec2(newCharaPoint.x, newCharaPoint.y+1.0f));
        } else if(random == 4) {
            chara->moveWorld(0.1f, Vec2(newCharaPoint.x-1.0f, newCharaPoint.y));
        }
        
//        CCLOG("mob%d X:%f Y:%f", i, chara->worldPosition().x, chara->worldPosition().y);
    }
}
