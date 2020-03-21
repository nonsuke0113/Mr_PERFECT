//
//  StageRightUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/01.
//

#include "StageRightUILayer.hpp"
#include "StageUILayer.hpp"

#pragma mark -
#pragma mark Init
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
    this->m_background = { Sprite::create("side_right.png") };
    this->m_background->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_background->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(this->m_background);
    
    // 自身のサイズ設定
    this->setContentSize(this->m_background->getContentSize());
    
    // タイム
    Label *timeLabel = Label::createWithTTF("TIME:", "fonts/PixelMplus12-Regular.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0,0));
    timeLabel->setPosition(Vec2(24.0f, 600.0f));
    timeLabel->setColor(Color3B(255, 255, 255));
    
    this->addChild(timeLabel);
    this->m_timeValueLabel = Label::createWithTTF("000", "fonts/PixelMplus12-Regular.ttf", 30);
    this->m_timeValueLabel->setAnchorPoint(Vec2(0,0));
    this->m_timeValueLabel->setPosition(Vec2(104.0f, 570.0f));
    this->m_timeValueLabel->setColor(Color3B(255, 255, 255));
    this->addChild(this->m_timeValueLabel);
    
    // Aボタン
    this->m_aButton = ui::Button::create("aButton.png");
    this->m_aButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_aButton->setPosition(Vec2(124.0f, 340.0f));
    this->m_aButton->addTouchEventListener(CC_CALLBACK_2(StageRightUILayer::touchAEvent, this));
    this->addChild(this->m_aButton);
    
    // Bボタン
    this->m_bButton = ui::Button::create("bButton.png");
    this->m_bButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_bButton->setPosition(Vec2(24.0f, 220.0f));
    this->m_bButton->addTouchEventListener(CC_CALLBACK_2(StageRightUILayer::touchBEvent, this));
    this->addChild(this->m_bButton);
    
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
    this->m_timeValueLabel->setString(StringUtils::format("%03d", (int)time));
}
