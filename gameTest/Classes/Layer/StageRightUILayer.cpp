//
//  StageRightUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/01.
//

#include "StageRightUILayer.hpp"
#include "StageUILayer.hpp"

#pragma mark -
#pragma mark init
/**
    初期化処理
 */
bool StageRightUILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 背景
    this->background = { Sprite::create("side.png") };
    this->background->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->background->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(this->background);
    
    // 自身のサイズ設定
    this->setContentSize(this->background->getContentSize());
    
    // タイム
    Label *timeLabel = Label::createWithTTF("TIME:", "fonts/PixelMplus12-Regular.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0,0));
    timeLabel->setPosition(Vec2(24.0f, 600.0f));
    timeLabel->setColor(Color3B(255, 255, 255));
    
    this->addChild(timeLabel);
    this->timeValueLabel = Label::createWithTTF("000", "fonts/PixelMplus12-Regular.ttf", 30);
    this->timeValueLabel->setAnchorPoint(Vec2(0,0));
    this->timeValueLabel->setPosition(Vec2(104.0f, 570.0f));
    this->timeValueLabel->setColor(Color3B(255, 255, 255));
    this->addChild(this->timeValueLabel);
    
    // Aボタン
    this->aButton = ui::Button::create("aButton.png");
    this->aButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->aButton->setPosition(Vec2(84.0f, 340.0f));
    this->aButton->addTouchEventListener(CC_CALLBACK_2(StageRightUILayer::touchAEvent, this));
    this->addChild(this->aButton);
    
    // Bボタン
    this->bButton = ui::Button::create("bButton.png");
    this->bButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->bButton->setPosition(Vec2(84.0f, 220.0f));
    this->bButton->addTouchEventListener(CC_CALLBACK_2(StageRightUILayer::touchBEvent, this));
    this->addChild(this->bButton);
    
    return true;
}


#pragma mark -
#pragma mark ButtonEvent
/**
    Aボタン押下時のイベント
 */
void StageRightUILayer::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            // 親に通知
            StageUILayer *parent = (StageUILayer*)this->getParent();
            parent->touchAEvent(pSender, type);
        }
            
        case ui::Widget::TouchEventType::MOVED:
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            break;
    }
}


/**
    Bボタン押下時のイベント
 */
void StageRightUILayer::touchBEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: {
            // 親に通知
            StageUILayer *parent = (StageUILayer*)this->getParent();
            parent->touchBEvent(pSender, type);
        }
            
        case ui::Widget::TouchEventType::MOVED:
        case ui::Widget::TouchEventType::ENDED:
        case ui::Widget::TouchEventType::CANCELED:
            break;
    }
}


#pragma mark -
#pragma mark Update
/**
    経過時間ラベルを更新する
 
    @param time 経過時間
 */
void StageRightUILayer::updateTime(float time)
{
    this->timeValueLabel->setString(StringUtils::format("%03d", (int)time));
}
