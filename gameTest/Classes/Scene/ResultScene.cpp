//
//  ResultScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/10.
//

#include "ResultScene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 
    @param time クリアタイム
    @param hp クリア時の残HP
    @param foundCnt クリア時の敵に見つかった回数
    @param rank クリアランク
 
    @return シーン
 */
Scene* ResultScene::createScene(int time, int hp, int foundCnt, int rank)
{
    auto scene = Scene::create();
    auto layer = ResultScene::create(time, hp, foundCnt, rank);
    scene->addChild(layer);
    return scene;
}


/**
    レイヤーの作成
 
    @param time クリアタイム
    @param hp クリア時の残HP
    @param foundCnt クリア時の敵に見つかった回数
    @param rank クリアランク
 
    @return レイヤー
 */
ResultScene* ResultScene::create(int time, int hp, int foundCnt, int rank)
{
    ResultScene *layer = new (std::nothrow) ResultScene();
    if (layer && layer->init(time, hp, foundCnt, rank))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}


/**
    初期化処理
 
    @param time クリアタイム
    @param hp クリア時の残HP
    @param foundCnt クリア時の敵に見つかった回数
    @param rank クリアランク
 */
bool ResultScene::init(int time, int hp, int foundCnt, int rank)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    
    // 背景
    Sprite *bgSprite { Sprite::create("title_background.png") };
    bgSprite->setPosition(visibleSize / 2);
    this->addChild(bgSprite);
    
    // リザルト
    Sprite *resultSprite = Sprite::create("result.png");
    resultSprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    resultSprite->setPosition(Vec2(568.f, 480.0f));
    this->addChild(resultSprite);
    
    // 経過時間
    Sprite *timeSprite = Sprite::create("time.png");
    timeSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    timeSprite->setPosition(Vec2(356.0f, 360.0f));
    this->addChild(timeSprite);
    Label *timeLabel = Label::createWithTTF(StringUtils::format("%d", time), "fonts/PixelMplus12-Regular.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0,0));
    timeLabel->setPosition(Vec2(600.0f, 360.0f));
    timeLabel->setColor(Color3B(0, 0, 0));
    this->addChild(timeLabel);
    
    // HP
    Sprite *hpSprite = Sprite::create("hp.png");
    hpSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    hpSprite->setPosition(Vec2(384.0f, 300.0f));
    this->addChild(hpSprite);
    Label *hpLabel = Label::createWithTTF(StringUtils::format("%d", hp), "fonts/PixelMplus12-Regular.ttf", 30);
    hpLabel->setAnchorPoint(Vec2(0,0));
    hpLabel->setPosition(Vec2(600.0f, 300.0f));
    hpLabel->setColor(Color3B(0, 0, 0));
    this->addChild(hpLabel);
    
    // 敵に見つかった数
    Sprite *foundSprite = Sprite::create("found.png");
    foundSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    foundSprite->setPosition(Vec2(350.0f, 240.0f));
    this->addChild(foundSprite);
    Label *foundLabel = Label::createWithTTF(StringUtils::format("%d", foundCnt), "fonts/PixelMplus12-Regular.ttf", 30);
    foundLabel->setAnchorPoint(Vec2(0,0));
    foundLabel->setPosition(Vec2(600.0f, 240.0f));
    foundLabel->setColor(Color3B(0, 0, 0));
    this->addChild(foundLabel);

    // ランク
    Sprite *rankSprite = Sprite::create("rank.png");
    rankSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    rankSprite->setPosition(Vec2(400.0f, 160.0f));
    this->addChild(rankSprite);
    Sprite *userRank = nullptr;
    switch (rank) {
        case 0:
            userRank = Sprite::create("pRank.png");
            break;
        case 1:
            userRank = Sprite::create("aRank.png");
            break;
        case 2:
            userRank = Sprite::create("bRank.png");
            break;
        case 3:
            userRank = Sprite::create("cRank.png");
            break;
        default:
            break;
    }
    userRank->setAnchorPoint(Vec2(0.0f, 1.0f));
    userRank->setPosition(Vec2(630.0f, 180.0f));
    this->addChild(userRank);
    
    return true;
}
