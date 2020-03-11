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
 */
Scene* ResultScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ResultScene::create();
    scene->addChild(layer);
    return scene;
}


/**
    初期化処理
 */
bool ResultScene::init()
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
    
    // HP
    Sprite *hpSprite = Sprite::create("hp.png");
    hpSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    hpSprite->setPosition(Vec2(384.0f, 300.0f));
    this->addChild(hpSprite);
    
    // 発見数
    Sprite *foundSprite = Sprite::create("found.png");
    foundSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    foundSprite->setPosition(Vec2(350.0f, 240.0f));
    this->addChild(foundSprite);

    // ランク
    Sprite *rankSprite = Sprite::create("rank.png");
    rankSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    rankSprite->setPosition(Vec2(400.0f, 160.0f));
    this->addChild(rankSprite);
    
    Sprite *rankSprite2 = Sprite::create("aRank.png");
    rankSprite2->setAnchorPoint(Vec2(0.0f, 1.0f));
    rankSprite2->setPosition(Vec2(630.0f, 180.0f));
    this->addChild(rankSprite2);
    
    return true;
}
