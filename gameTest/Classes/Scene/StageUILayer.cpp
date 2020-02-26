//
//  StageUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/26.
//

#include "StageUILayer.hpp"

#pragma mark -
#pragma mark init
/**
    初期化処理
 */
bool StageUILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    Size visibleSize { Director::getInstance()->getVisibleSize() };

    // パッド下地
    this->padBack = { Sprite::create("virtualPad_background.png") };
//    this->padBack->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->padBack->setPosition(Vec2(24.0f + this->padBack->getContentSize().width / 2, (visibleSize.height / 2)));
    this->addChild(this->padBack);
    
    // パッド操作部
    this->padPick = { Sprite::create("virtualPad_pick.png") };
//    this->padPick->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->padPick->setPosition(Vec2(84.0f + this->padPick->getContentSize().width / 2, (visibleSize.height / 2) ));
    this->addChild(this->padPick);
    
    //
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(StageUILayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(StageUILayer::onTouchesMoved, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


/**
 */
void StageUILayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        Rect padPickRect = this->padPick->getBoundingBox();
        if (padPickRect.containsPoint(location)) {
            this->padPick->setPosition(location);
        }
        iterator++;
    }
    return;
}


/**
 */
void StageUILayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        Rect padPickRect = this->padPick->getBoundingBox();
        if (padPickRect.containsPoint(location)) {
            this->padPick->setPosition(location);
        }
        iterator++;
    }
    return;
}
