//
//  ResultScene.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/10.
//

#include "ResultScene.hpp"
#include "SelectMissonScene.hpp"
#include "ShareLauncher.h"

#pragma mark -
#pragma mark Init
/**
    シーンの作成
 
    @param resultInfo リザルト情報
    @return シーン
 */
Scene* ResultScene::createScene(::resultInfo resultInfo)
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
ResultScene* ResultScene::create(::resultInfo resultInfo)
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
bool ResultScene::init(::resultInfo resultInfo)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
//    this->m_isViewedRank = false;
    
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
    resultSprite->setPosition(Vec2(568.0f, 576.0f));
    this->addChild(resultSprite);
        
    // ステージラベル
    Label *stageLabel = Label::createWithTTF(StringUtils::format("MISSION%d", this->m_resultInfo.clearStage), "fonts/PixelMplus12-Regular.ttf", 30);
    stageLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
    stageLabel->setPosition(Vec2(568.0f, 476.0f));
    stageLabel->setColor(Color3B(0, 0, 0));
    this->addChild(stageLabel);
    
    // 経過時間
    Sprite *timeSprite = Sprite::create("time.png");
    timeSprite->setAnchorPoint(Vec2(1.0f, 0.0f));
    timeSprite->setPosition(Vec2(300.0f, 370.0f));
    this->addChild(timeSprite);
    Label *timeLabel = Label::createWithTTF(StringUtils::format("%03d     %05d     %s", this->m_resultInfo.clearTime, this->m_resultInfo.timeScore, this->convertRankStr(this->m_resultInfo.timeScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    timeLabel->setPosition(Vec2(360.0f, 373.0f));
    timeLabel->setColor(Color3B(0, 0, 0));
    this->addChild(timeLabel);
    
    // HP
    Sprite *hpSprite = Sprite::create("hp.png");
    hpSprite->setAnchorPoint(Vec2(1.0f, 0.0f));
    hpSprite->setPosition(Vec2(300.0f, 286.0f));
    this->addChild(hpSprite);
    Label *hpLabel = Label::createWithTTF(StringUtils::format("%d/3     %05d     %s", this->m_resultInfo.clearHp, this->m_resultInfo.hpScore, this->convertRankStr(this->m_resultInfo.hpScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    hpLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    hpLabel->setPosition(Vec2(360.0f, 290.0f));
    hpLabel->setColor(Color3B(0, 0, 0));
    this->addChild(hpLabel);
    
    // 敵に見つかった数
    Sprite *foundSprite = Sprite::create("found.png");
    foundSprite->setAnchorPoint(Vec2(1.0f, 0.0f));
    foundSprite->setPosition(Vec2(300.0f, 195.0f));
    this->addChild(foundSprite);
    Label *foundLabel = Label::createWithTTF(StringUtils::format("%03d     %05d     %s", this->m_resultInfo.clearFoundCount, this->m_resultInfo.foundScore,  this->convertRankStr(this->m_resultInfo.foundScore).c_str()), "fonts/PixelMplus12-Regular.ttf", 30);
    foundLabel->setAnchorPoint(Vec2(0,0));
    foundLabel->setPosition(Vec2(360.0f, 200.0f));
    foundLabel->setColor(Color3B(0, 0, 0));
    this->addChild(foundLabel);

    // スコア
    Sprite *scoreSprite = Sprite::create("totalscore.png");
    scoreSprite->setAnchorPoint(Vec2(1.0f, 0.0f));
    scoreSprite->setPosition(Vec2(404.0f, 64.0f));
    this->addChild(scoreSprite);
    int totalScore = (int)this->m_resultInfo.timeScore + (int)this->m_resultInfo.hpScore + (int)this->m_resultInfo.foundScore;
    Label *scoreLabel = Label::createWithTTF(StringUtils::format("%05d", totalScore), "fonts/PixelMplus12-Regular.ttf", 30);
    scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    scoreLabel->setPosition(Vec2(478.0f, 64.0f));
    scoreLabel->setColor(Color3B(0, 0, 0));
    this->addChild(scoreLabel);
    
    // ランク
    Sprite *rankSprite = Sprite::create("rank.png");
    rankSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    rankSprite->setPosition(Vec2(756.0f, 370.0f));
    this->addChild(rankSprite);
    if (totalScore >= TOTAL_SCORE_P_STANDARD) {
        this->m_userRankSprite = Sprite::create("rank_P.png");
    } else if (totalScore >= TOTAL_SCORE_A_STANDARD) {
        this->m_userRankSprite = Sprite::create("rank_A.png");
    } else if (totalScore >= TOTAL_SCORE_B_STANDARD) {
        this->m_userRankSprite = Sprite::create("rank_B.png");
    } else {
        this->m_userRankSprite = Sprite::create("rank_C.png");
    }
    this->m_userRankSprite->setScale(3.0f);
    this->m_userRankSprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_userRankSprite->setPosition(Vec2(790.0f, 64.0f));
    this->addChild(this->m_userRankSprite);
    
    // シェア
    ui::Button *shareButton = ui::Button::create("share.png");
    shareButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    shareButton->setPosition(Vec2(1136.0f, 640.0f));
    shareButton->addTouchEventListener(CC_CALLBACK_2(ResultScene::touchShareEvent, this));
    this->addChild(shareButton);
    
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
    // ミッション選択シーンに遷移
    Vector<FiniteTimeAction *> actionAry;
    actionAry.pushBack(CallFunc::create([this]() {
        Scene *selectMissionScene = SelectMissonScene::createScene();
        TransitionFade* fade = TransitionFade::create(1.0f, selectMissionScene);
        Director::getInstance()->replaceScene(fade);
    }));
    Sequence *actions = Sequence::create(actionAry);
    this->m_userRankSprite->runAction(actions);
    return;
}


/**
    共有ボタン押下時のイベント
 */
void ResultScene::touchShareEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            // スクリーンショットのテクスチャを取得する
            Size visibleSize = Director::getInstance()->getVisibleSize();
            RenderTexture* texture = RenderTexture::create((int)visibleSize.width, (int)visibleSize.height);
            texture->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
            texture->begin();
            Director::getInstance()->getRunningScene()->visit();
            texture->end();

            // 取得したテクスチャを保存する
            texture->saveToFile("screenshot.png", Image::Format::PNG, true, [&](RenderTexture* rt, const std::string& path) {
                // 保存完了のコールバック処理
                std::string text = StringUtils::format("MIISION%dをクリア！ #MrPerfect", this->m_resultInfo.clearStage);
                ShareLauncher::openShareDialog(text, path);
            });
            break;
        }
        default:
            break;
    }
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
    if (score >= SCORE_A_STANDARD_BY_ITEM) {
        rankStr = "A";
    } else if (score >= SCORE_B_STANDARD_BY_ITEM) {
        rankStr = "B";
    } else {
        rankStr = "C";
    }
    
    return rankStr;
}
