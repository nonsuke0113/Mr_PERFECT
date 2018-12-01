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

bool pushedUpButton;
bool pushedRightButton;
bool pushedDownButton;
bool pushedLeftButton;

const float VIEW_HEGHT = 640.0f; // 画面の高さ(pixel)
const float VIEW_WIDTH = 960.0f; // 画面の幅(pixel)

const float SIDE_BAR_WIDTH = 160.0f; // サイドバーの幅(pixel)

const int MAP_TILE_HEGHT = 40; // MAPの高さ(Tile)
const int MAP_TILE_WIDTH = 40; // MAPの幅(Tile)

// 十字ボタンタグ
enum {
    TAG_UP = 10,
    TAG_RIGHT = 20,
    TAG_DOWN = 30,
    TAG_LEFT = 40,
};

// プレイヤー向きの定数
const int PLAYER_BACK = 1;
const int PLAYER_RIGHT  = 2;
const int PLAYER_FRONT  = 3;
const int PLAYER_LEFT = 4;

// プレイヤー向き
int playerDirectcion = PLAYER_FRONT;



/**
 */

Scene* MainGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    layer->pCamera = scene->getDefaultCamera();
    Camera* camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    layer->addChild(camera);
    scene->addChild(layer);
    return scene;
}


/**
 */
bool MainGameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    // マップ表示
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
    this->pPlayer = Sprite::create("chara_test.png");
    this->pPlayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->pPlayer->setPosition(Vec2(512.0f, 320.0f));
    this->addChild(this->pPlayer);
    this->pPlayerMapPoint = Point {16,29};
    
    // モブキャラクター
    this->mob1 = CharacterSprite::create("mob_test.png",Vec2(10.0f, 10.0f));
    this->mob1->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(this->mob1);
    
    // ラベル
    this->playerMapPointLabel = Label::createWithSystemFont(StringUtils::format("x : $%f, y : $%f", this->pPlayerMapPoint.x, this->pPlayerMapPoint.y), "ariel", 20);
    this->playerMapPointLabel->setAnchorPoint(Vec2(0,0));
    this->playerMapPointLabel->setPosition(Vec2(0.0f, 0.0f));
    this->playerMapPointLabel->setColor(Color3B(255, 0, 0));
    this->playerMapPointLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(playerMapPointLabel);
    
    schedule(schedule_selector(MainGameScene::updatePosition), 0.1f);
    schedule(schedule_selector(MainGameScene::updateMob1Position), 2.0f);
    
    CCLOG("player X:%f Y:%f", this->pPlayer->getPositionX(), this->pPlayer->getPositionY());
    
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
                    playerDirectcion = PLAYER_BACK;
                    pushedUpButton = true;
                    break;
                case TAG_RIGHT:
                    playerDirectcion = PLAYER_RIGHT;
                    pushedRightButton = true;
                    break;
                case TAG_DOWN:
                    playerDirectcion = PLAYER_FRONT;
                    pushedDownButton = true;
                    break;
                case TAG_LEFT:
                    playerDirectcion = PLAYER_LEFT;
                    pushedLeftButton = true;
                    break;
                default:
                    break;
            }
            
            break;
        }
            
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
        {
            switch (buttonType) {
                case TAG_UP:
                    pushedUpButton = false;
                    break;
                case TAG_RIGHT:
                    pushedRightButton = false;
                    break;
                case TAG_DOWN:
                    pushedDownButton = false;
                    break;
                case TAG_LEFT:
                    pushedLeftButton = false;
                    break;
                default:
                    break;
            }
            break;
        }
            
        default:
            break;
            
    }
}


/**
 */
void MainGameScene::updatePosition(float frame) {
    
    // 十字キーが押されてなかったり、行けない道だったら何もしない
    if ((!pushedUpButton && !pushedRightButton && !pushedDownButton && !pushedLeftButton) ||
        (this->pMap->getNumberOfRunningActions() > 0) ||
        (this->pPlayer->getNumberOfRunningActions() > 0) ||
        checkNextTileGID() != 29 ||
        checkNextTileMob()) {
        return;
    }
    
    //
    Vec3 newTileMapPoint = this->pCamera->getPosition3D();
    //
    Point newPlayerPoint = this->pPlayer->getPosition();
    
    MoveTo* actionMove;
    
    // 上ボタン押下中
    if (pushedUpButton) {
        if((newTileMapPoint.y != ((PER_TILE_SIZE * MAP_TILE_HEGHT) - VIEW_HEGHT/2)) &&
        (newTileMapPoint.y == newPlayerPoint.y)) {
            newTileMapPoint.y += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newTileMapPoint);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        newPlayerPoint.y += PER_TILE_SIZE;
        actionMove = MoveTo::create(0.1f, newPlayerPoint);
        this->pPlayer->stopAllActions();
        this->pPlayer->runAction(actionMove);
        pPlayerMapPoint.y--;
    }
    
    // 右ボタン押下中
    if (pushedRightButton) {
        if((newTileMapPoint.x != (PER_TILE_SIZE * MAP_TILE_WIDTH) - VIEW_WIDTH/2 + SIDE_BAR_WIDTH) &&
           (newTileMapPoint.x == newPlayerPoint.x)) {
            newTileMapPoint.x += PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newTileMapPoint);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        newPlayerPoint.x += PER_TILE_SIZE;
        actionMove = MoveTo::create(0.1f, newPlayerPoint);
        this->pPlayer->stopAllActions();
        this->pPlayer->runAction(actionMove);
        pPlayerMapPoint.x++;
    }
    
    // 下ボタン押下中
    if (pushedDownButton) {
        if ((newTileMapPoint.y != VIEW_HEGHT/2) &&
            (newTileMapPoint.y == newPlayerPoint.y)){
            newTileMapPoint.y -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newTileMapPoint);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        newPlayerPoint.y -= PER_TILE_SIZE;
        actionMove = MoveTo::create(0.1f, newPlayerPoint);
        this->pPlayer->stopAllActions();
        this->pPlayer->runAction(actionMove);
        pPlayerMapPoint.y++;
    }
    
    // 左ボタン押下中
    if (pushedLeftButton) {
        if((newTileMapPoint.x != VIEW_WIDTH/2 - SIDE_BAR_WIDTH) &&
           (newTileMapPoint.x == newPlayerPoint.x)){
            newTileMapPoint.x -= PER_TILE_SIZE;
            actionMove = MoveTo::create(0.1f, newTileMapPoint);
            this->pCamera->stopAllActions();
            this->pCamera->runAction(actionMove);
        }
        newPlayerPoint.x -= PER_TILE_SIZE;
        actionMove = MoveTo::create(0.1f, newPlayerPoint);
        this->pPlayer->stopAllActions();
        this->pPlayer->runAction(actionMove);
        pPlayerMapPoint.x--;
    }
    
    // DEBUG:現在いる位置のラベルを更新
    this->playerMapPointLabel->setString(StringUtils::format("x : $%f, y : $%f", this->pPlayerMapPoint.x, this->pPlayerMapPoint.y));
    
    // 今いるタイルを判定
    TMXLayer* layer = this->pMap->getLayer("Ground");
    int tileGID = layer->getTileGIDAt(pPlayerMapPoint)-1;
    CCLOG("タイルID:%d", tileGID);
    CCLOG("player X:%f Y:%f", this->pPlayer->getPositionX(), this->pPlayer->getPositionY());
    CCLOG("camera X:%f Y:%f", this->pCamera->getPositionX(), this->pCamera->getPositionY());

}

/**
 */
void MainGameScene::updateMob1Position(float frame) {
    
    if (this->mob1->getNumberOfRunningActions() > 0) {
        return;
    }
    
    Vec2 newMob1Point = this->mob1->worldPosition;
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
    
    CCLOG("mob1 X:%f Y:%f", this->mob1->worldPosition.x,this->mob1->worldPosition.y);
}

/**
 */
int MainGameScene::checkNextTileGID()  {
    
    int tileGID = -1;
    TMXLayer* layer = this->pMap->getLayer("Ground");
    Point point = { -1, -1 };
    
    if(playerDirectcion == PLAYER_BACK && pPlayerMapPoint.y != 0) {
        point = Point { pPlayerMapPoint.x, pPlayerMapPoint.y-1 };
    }
    else if(playerDirectcion == PLAYER_RIGHT && pPlayerMapPoint.x != MAP_TILE_WIDTH-1) {
        point = Point { pPlayerMapPoint.x+1, pPlayerMapPoint.y };
    }
    else if (playerDirectcion == PLAYER_FRONT && pPlayerMapPoint.y != MAP_TILE_HEGHT-1) {
        point = Point { pPlayerMapPoint.x, pPlayerMapPoint.y+1 };
    }
    else if (playerDirectcion == PLAYER_LEFT && pPlayerMapPoint.x != 0) {
        point = Point { pPlayerMapPoint.x-1, pPlayerMapPoint.y };
    }
    
    if(point.x != -1 && point.x != MAP_TILE_WIDTH &&
       point.y != -1 && point.y != MAP_TILE_HEGHT) {
        tileGID = layer->getTileGIDAt(point)-1;
    }
    
    return tileGID;
}

/**
 */
bool MainGameScene::checkNextTileMob()  {
    
    Vec2 nextTilePosition = this->pPlayer->getPosition();
    
    if(playerDirectcion == PLAYER_BACK && pPlayerMapPoint.y != 0) {
        nextTilePosition = Point { nextTilePosition.x, nextTilePosition.y+PER_TILE_SIZE };
    }
    else if(playerDirectcion == PLAYER_RIGHT && pPlayerMapPoint.x != MAP_TILE_WIDTH-1) {
        nextTilePosition = Point { nextTilePosition.x+PER_TILE_SIZE, nextTilePosition.y };
    }
    else if (playerDirectcion == PLAYER_FRONT && pPlayerMapPoint.y != MAP_TILE_HEGHT-1) {
        nextTilePosition = Point { nextTilePosition.x, nextTilePosition.y-PER_TILE_SIZE };
    }
    else if (playerDirectcion == PLAYER_LEFT && pPlayerMapPoint.x != 0) {
        nextTilePosition = Point { nextTilePosition.x-PER_TILE_SIZE, nextTilePosition.y };
    }
    
    if(nextTilePosition == this->mob1->getPosition()) {
        return true;
    }
    return false;
}
