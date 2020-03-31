//
//  ResultScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/10.
//

#include "ResultScene.hpp"
#include "SelectMissonScene.hpp"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 
    @param resultInfo リザルト情報
    @return シーン
 */
Scene* ResultScene::createScene(::resultInfo *resultInfo)
{
    auto scene = Scene::create();
    auto layer = ResultScene::create(resultInfo);
    scene->addChild(layer);
    return scene;
}


/**
    レイヤーの作成
 
    @param resultInfo リザルト情報
    @return レイヤー
 */
ResultScene* ResultScene::create(::resultInfo *resultInfo)
{
    ResultScene *layer = new (std::nothrow) ResultScene();
    if (layer && layer->init(resultInfo))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}


/**
    初期化処理
 
    @param resultInfo リザルト情報
 */
bool ResultScene::init(::resultInfo *resultInfo)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->m_isViewedRank = false;
    
    // リザルト設定
    this->m_resultInfo = resultInfo;
    
    // 画面サイズ取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 背景
    Sprite *bgSprite { Sprite::create("title_background.png") };
    bgSprite->setPosition(visibleSize / 2);
    this->addChild(bgSprite);
    
    // リザルト
    Sprite *resultSprite = Sprite::create("result.png");
    resultSprite->setAnchorPoint(Vec2(0.5f, 1.0f));
    resultSprite->setPosition(Vec2(568.f, 540.0f));
    this->addChild(resultSprite);
    
    // 経過時間
    Sprite *timeSprite = Sprite::create("time.png");
    timeSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    timeSprite->setPosition(Vec2(240.0f, 388.0f));
    this->addChild(timeSprite);
    Label *timeLabel = Label::createWithTTF(StringUtils::format("%03d       %05d       %s", this->m_resultInfo->clearTime, this->m_resultInfo->timeScore, this->convertRankStr(this->m_resultInfo->timeScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0,0));
    timeLabel->setPosition(Vec2(468.0f, 388.0f));
    timeLabel->setColor(Color3B(0, 0, 0));
    this->addChild(timeLabel);
    
    // HP
    Sprite *hpSprite = Sprite::create("hp.png");
    hpSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    hpSprite->setPosition(Vec2(270.0f, 324.0f));
    this->addChild(hpSprite);
    Label *hpLabel = Label::createWithTTF(StringUtils::format("%d/3       %05d       %s", this->m_resultInfo->clearHp, this->m_resultInfo->hpScore, this->convertRankStr(this->m_resultInfo->hpScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    hpLabel->setAnchorPoint(Vec2(0,0));
    hpLabel->setPosition(Vec2(468.0f, 324.0f));
    hpLabel->setColor(Color3B(0, 0, 0));
    this->addChild(hpLabel);
    
    // 敵に見つかった数
    Sprite *foundSprite = Sprite::create("found.png");
    foundSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    foundSprite->setPosition(Vec2(225.0f, 258.0f));
    this->addChild(foundSprite);
    Label *foundLabel = Label::createWithTTF(StringUtils::format("%03d       %05d       %s", this->m_resultInfo->clearFoundCount, this->m_resultInfo->foundScore,  this->convertRankStr(this->m_resultInfo->foundScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    foundLabel->setAnchorPoint(Vec2(0,0));
    foundLabel->setPosition(Vec2(468.0f, 258.0f));
    foundLabel->setColor(Color3B(0, 0, 0));
    this->addChild(foundLabel);

    // スコア
    Sprite *scoreSprite = Sprite::create("score.png");
    scoreSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    scoreSprite->setPosition(Vec2(420.0f, 170.0f));
    this->addChild(scoreSprite);
    Label *scoreLabel = Label::createWithTTF(StringUtils::format("%d", this->m_resultInfo->timeScore + this->m_resultInfo->hpScore + this->m_resultInfo->foundScore), "fonts/PixelMplus12-Regular.ttf", 30);
    scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    scoreLabel->setPosition(Vec2(620.0f, 170.0f));
    scoreLabel->setColor(Color3B(0, 0, 0));
    this->addChild(scoreLabel);
    
    // ランク
    Sprite *rankSprite = Sprite::create("rank.png");
    rankSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    rankSprite->setPosition(Vec2(420.0f, 100.0f));
    this->addChild(rankSprite);
    
    // イベントリスナーを設定
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(ResultScene::onTouchesBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


#pragma mark -
#pragma mark TouchEvent
/**
    タッチ時に呼び出される
 */
void ResultScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    // 一回表示済みなら何もしない
    if (this->m_isViewedRank) {
        return;
    }
    this->m_isViewedRank = true;
    
    Sprite *userRank = nullptr;
    int totalScore = (int)this->m_resultInfo->timeScore + (int)this->m_resultInfo->hpScore + (int)this->m_resultInfo->foundScore;
    if (totalScore >= 9000) {
        userRank = Sprite::create("rank_P.png");
    } else if (totalScore >= 6000) {
        userRank = Sprite::create("rank_A.png");
    } else if (totalScore >= 3000) {
        userRank = Sprite::create("rank_B.png");
    } else {
        userRank = Sprite::create("rank_C.png");
    }
    userRank->setAnchorPoint(Vec2(0.0f, 0.0f));
    userRank->setPosition(Vec2(-userRank->getContentSize().width, 80.0f));
    this->addChild(userRank);
    
    // 画面サイズ取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(MoveTo::create(0.5f, Vec2(616.0f, 80.0f)));
    actionAry.pushBack(MoveTo::create(1.0f, Vec2(616.0f, 80.0f)));
//    actionAry.pushBack(MoveTo::create(0.3f, Vec2(visibleSize.width + userRank->getContentSize().width, 100.0f)));
    actionAry.pushBack(Hide::create());
    
    // ミッション選択シーンに遷移
    actionAry.pushBack(CallFunc::create([this]() {
        Scene *selectMissionScene = SelectMissonScene::createScene();
        TransitionFade* fade = TransitionFade::create(1.0f, selectMissionScene);
        Director::getInstance()->replaceScene(fade);
    }));
    Sequence *actions = Sequence::create(actionAry);
    userRank->runAction(actions);
    return;
}


#pragma mark -
/**
    スコアを文字列に変換する
 
    @param score スコア
    @return 変換した文字列
 */
std::string ResultScene::convertRankStr(int score)
{
    std::string rankStr = "";
    if (score >= 3000) {
        rankStr = "A";
    } else if (score >= 2000) {
        rankStr = "B";
    } else {
        rankStr = "C";
    }
    
    return rankStr;
}
