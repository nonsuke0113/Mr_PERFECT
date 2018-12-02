//
//  MainGameScene.cpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#include "MainGameScene.hpp"
#include "Const.hpp"

USING_NS_CC;

//
enum pushedButton {
    pushedButtonNone,
    isPushedUpButton,
    isPushedRightButton,
    isPushedDownButton,
    isPushedLeftButton
};
//
pushedButton m_isPushedButton = pushedButtonNone;

// 十字ボタンタグ
enum crossKeyTag {
    TAG_UP = 10,
    TAG_RIGHT = 20,
    TAG_DOWN = 30,
    TAG_LEFT = 40
};

// プレイヤー向き
enum playerDirectcion {
    player_back,
    player_right,
    player_front,
    player_left
};
//
playerDirectcion m_playerDirectcion = player_front;


Scene* MainGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    
    // スクロール用カメラを追加
    layer->pCamera = scene->getDefaultCamera();
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
    
    // キャラクター
    this->pPlayer = CharacterSprite::create("chara_test.png", Vec2(16.0f, 29.0f), this->pMap);
    this->pPlayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->pPlayer);
    
    // モブキャラクター
    this->mob1 = CharacterSprite::create("mob_test.png", Vec2(10.0f, 29.0f), this->pMap);
    this->mob1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->mob1);
    
    // ラベル
    this->playerMapPointLabel = Label::createWithSystemFont(StringUtils::format("x : $%f, y : $%f", this->pPlayer->worldPosition().x, this->pPlayer->worldPosition().y), "ariel", 20);
    this->playerMapPointLabel->setAnchorPoint(Vec2(0,0));
    this->playerMapPointLabel->setPosition(Vec2(0.0f, 0.0f));
    this->playerMapPointLabel->setColor(Color3B(255, 0, 0));
    this->playerMapPointLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(playerMapPointLabel);
    
    // 座標更新をスケジュール
    schedule(schedule_selector(MainGameScene::updatePosition), 0.1f);
//    schedule(schedule_selector(MainGameScene::updateMob1Position), 2.0f);
    
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
 座標更新処理
 */
void MainGameScene::updatePosition(float frame) {
    
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((m_isPushedButton == pushedButtonNone) ||
        (this->pMap->getNumberOfRunningActions() > 0) ||
        (this->pPlayer->getNumberOfRunningActions() > 0) ||
        this->pPlayer->getNextTileGID() != 29 ||
        checkNextTileMob()) {
        return;
    }
    
    // カメラ座標
    Vec3 newCameraPosition = this->pCamera->getPosition3D();
    MoveTo* actionMove;
    //
    Vec2 newPlayerPosition = this->pPlayer->worldPosition();
    
    // 上ボタン押下中
    if (m_isPushedButton == isPushedUpButton) {
        if((newCameraPosition.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT/2)) &&
        (newCameraPosition.y == this->pPlayer->getPosition().y)) {
            newCameraPosition.y += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        //
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x, newPlayerPosition.y-1.0f));
    }
    
    // 右ボタン押下中
    if (m_isPushedButton == isPushedRightButton) {
        if((newCameraPosition.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH) &&
           (newCameraPosition.x == this->pPlayer->getPosition().x)) {
            newCameraPosition.x += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        //
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x+1.0f, newPlayerPosition.y));
    }
    
    // 下ボタン押下中
    if (m_isPushedButton == isPushedDownButton) {
        if ((newCameraPosition.y != VIEW_HEGHT/2) &&
            (newCameraPosition.y == this->pPlayer->getPosition().y)){
            newCameraPosition.y -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        //
        this->pPlayer->moveWorld(0.1f, Vec2(newPlayerPosition.x, newPlayerPosition.y+1.0f));
    }
    
    // 左ボタン押下中
    if (m_isPushedButton == isPushedLeftButton) {
        if((newCameraPosition.x != VIEW_WIDTH/2 - SIDE_BAR_WIDTH) &&
           (newCameraPosition.x == this->pPlayer->getPosition().x)){
            newCameraPosition.x -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newCameraPosition);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        //
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
 */
void MainGameScene::updateMob1Position(float frame) {
    
    if (this->mob1->getNumberOfRunningActions() > 0) {
        return;
    }
    
    Vec2 newMob1Point = this->mob1->worldPosition();
    int random = rand()%4+1;
    if(random == 1) {
        this->mob1->moveWorld(0.1f, Vec2(newMob1Point.x, newMob1Point.y-1.0f));
    } else if(random == 2) {
        this->mob1->moveWorld(0.1f, Vec2(newMob1Point.x+1.0f, newMob1Point.y));
    } else if(random == 3) {
        this->mob1->moveWorld(0.1f, Vec2(newMob1Point.x, newMob1Point.y+1.0f));
    } else if(random == 4) {
        this->mob1->moveWorld(0.1f, Vec2(newMob1Point.x-1.0f, newMob1Point.y));
    }
    
    CCLOG("mob1 X:%f Y:%f", this->mob1->worldPosition().x,this->mob1->worldPosition().y);
}


/**
 */
bool MainGameScene::checkNextTileMob()  {
    
    Vec2 nextTilePosition = this->pPlayer->getPosition();
    
    if(m_playerDirectcion == player_back && this->pPlayer->worldPosition().y != 0.0f) {
        nextTilePosition = Vec2 { nextTilePosition.x, nextTilePosition.y+PER_TILE_SIZE };
    }
    else if(m_playerDirectcion == player_right && this->pPlayer->worldPosition().x != MAP_TILE_WIDTH-1.0f) {
        nextTilePosition = Vec2 { nextTilePosition.x+PER_TILE_SIZE, nextTilePosition.y };
    }
    else if (m_playerDirectcion == player_front && this->pPlayer->worldPosition().y != MAP_TILE_HEGHT-1.0f) {
        nextTilePosition = Vec2 { nextTilePosition.x, nextTilePosition.y-PER_TILE_SIZE };
    }
    else if (m_playerDirectcion == player_left && this->pPlayer->worldPosition().x != 0.0f) {
        nextTilePosition = Vec2 { nextTilePosition.x-PER_TILE_SIZE, nextTilePosition.y };
    }
    
    if(nextTilePosition == this->mob1->getPosition()) {
        return true;
    }
    return false;
}
