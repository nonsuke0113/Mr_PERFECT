//
//  StageUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/26.
//

#include "StageUILayer.hpp"
#include <math.h>

#pragma mark -
#pragma mark init

static Vec2 _defaultPickPos; // パッド操作部の基準座標

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
    this->padBack->setPosition(Vec2(24.0f + this->padBack->getContentSize().width / 2, (visibleSize.height / 2)));
    this->addChild(this->padBack);
    
    // パッド操作部
    this->padPick = { Sprite::create("virtualPad_pick.png") };
    this->padPick->setPosition(Vec2(84.0f + this->padPick->getContentSize().width / 2, (visibleSize.height / 2)));
    this->addChild(this->padPick);
    
    // 基準座標を設定
    _defaultPickPos = this->padPick->getPosition();
    
    // イベントリスナーを設定
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(StageUILayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(StageUILayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(StageUILayer::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->padPick);
    
    return true;
}


/**
    タッチ時に呼び出される
 */
void StageUILayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        Vec2 location = touch->getLocation();
        Rect padPickRect = this->padPick->getBoundingBox();
        if (padPickRect.containsPoint(location)) {
            
            if (location.x > _defaultPickPos.x + this->padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x + this->padPick->getContentSize().width / 2;
            } else if (location.x < _defaultPickPos.x - this->padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x - this->padPick->getContentSize().width / 2;
            }
            
            if (location.y > _defaultPickPos.y + this->padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y + this->padPick->getContentSize().height / 2;
            } else if (location.y < _defaultPickPos.y - this->padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y - this->padPick->getContentSize().height / 2;
            }

            this->padPick->setPosition(location);
        }
        iterator++;
    }
    return;
}


/**
    ドラッグ時に呼び出される
 */
void StageUILayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        Rect padPickRect = this->padPick->getBoundingBox();
            
        if (location.x > _defaultPickPos.x + this->padPick->getContentSize().width / 2) {
            location.x = _defaultPickPos.x + this->padPick->getContentSize().width / 2;
        } else if (location.x < _defaultPickPos.x - this->padPick->getContentSize().width / 2) {
            location.x = _defaultPickPos.x - this->padPick->getContentSize().width / 2;
        }
        
        if (location.y > _defaultPickPos.y + this->padPick->getContentSize().height / 2) {
            location.y = _defaultPickPos.y + this->padPick->getContentSize().height / 2;
        } else if (location.y < _defaultPickPos.y - this->padPick->getContentSize().height / 2) {
            location.y = _defaultPickPos.y - this->padPick->getContentSize().height / 2;
        }
        
        this->padPick->setPosition(location);
        
        iterator++;
    }
    return;
}


/**
    タッチ終了時に呼び出される
 */
void StageUILayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    this->padPick->setPosition(_defaultPickPos);
}


/**
    バーチャルパッドの状態を返却する
 
    @return バーチャルパッドの向き
 */
::padState StageUILayer::padState()
{
    if (_defaultPickPos == this->padPick->getPosition()) {
        return ::padNone;
    }
    
    double degree = this->degreeFromVec2(_defaultPickPos, this->padPick->getPosition());
    
    if (degree >= 45.0 && degree < 135.0) {
        return ::padUp;
    } else if ((degree >= 0 && degree < 45.0) || (degree <= 0 && degree >= -45.0)) {
        return ::padRight;
    } else if (degree < -45.0 && degree >= -135.0) {
        return ::padDown;
    } else if ((degree <= -135.0 && degree >= 180.0) || (degree >= 135 && degree <= 180.0)) {
        return ::padLeft;
    }
    
    return ::padNone;
}


/**
    2点の座標から角度を計算して返す
 
    @param posA 1つ目の点の座標
    @param posB 2つ目の点の座標
    @return 角度
 */
double StageUILayer::degreeFromVec2(Vec2 posA, Vec2 posB)
{
    double radian = atan2(posB.y - posA.y, posB.x - posA.x);
    double degree = radian * 180.0 / M_PI;
    return degree;
}
