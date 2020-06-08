//
//  StageLeftUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/29.
//

#include "StageLeftUILayer.hpp"
#include <math.h>
#include "GameConst.hpp"

static Vec2 _defaultPickPos; // パッド操作部の基準座標

#pragma mark -
#pragma mark Init
/**
    初期化処理
 */
bool StageLeftUILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 背景
    this->m_background = { Sprite::create("side_left.png") };
    this->m_background->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_background->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(this->m_background);
    
    // 自身のサイズ設定
    this->setContentSize(this->m_background->getContentSize());
    
    // 画面サイズ取得
    Size visibleSize { Director::getInstance()->getVisibleSize() };
    
    // HP
    Label *hpLabel = Label::createWithTTF("HP:", "fonts/PixelMplus12-Regular.ttf", 30);
    hpLabel->setAnchorPoint(Vec2(0,0));
    hpLabel->setPosition(Vec2(24.0f, 600.0f));
    hpLabel->setColor(Color3B(255, 255, 255));
    this->addChild(hpLabel);
    
    this->m_heartes = Vector<Sprite*>();
    for (int i = 0; i < 3; i++) {
        
        Sprite *heartOff = Sprite::create("heart_off.png");
        heartOff->setAnchorPoint(Vec2(0.0f, 0.0f));
        heartOff->setPosition(Vec2(24.5f + ((heartOff->getContentSize().width + 24.5f) * i), 570.0f - heartOff->getContentSize().height / 2));
        this->addChild(heartOff);
        
        Sprite *heartOn = Sprite::create("heart_on.png");
        heartOn->setAnchorPoint(Vec2(0.0f, 0.0f));
        heartOn->setPosition(Vec2(24.5f + ((heartOn->getContentSize().width + 24.5f) * i), 570.0f - heartOn->getContentSize().height / 2));
        this->addChild(heartOn);
        this->m_heartes.pushBack(heartOn);
    }
    
    
    // パッド下地
    this->m_padBack = { Sprite::create("virtualPad_background.png") };
    this->m_padBack->setPosition(Vec2(24.0f + this->m_padBack->getContentSize().width / 2, (visibleSize.height / 2)));
    this->addChild(this->m_padBack);
    
    // パッド操作部
    this->m_padPick = { Sprite::create("virtualPad_pick.png") };
    this->m_padPick->setPosition(Vec2(84.0f + this->m_padPick->getContentSize().width / 2, (visibleSize.height / 2)));
    this->addChild(this->m_padPick);
    
    // 基準座標を設定
    _defaultPickPos = this->m_padPick->getPosition();
    
    // イベントリスナーを設定
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(StageLeftUILayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(StageLeftUILayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(StageLeftUILayer::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->m_padPick);
    
    return true;
}


#pragma mark -
#pragma mark TouchEvent
/**
    タッチ時に呼び出される
 */
void StageLeftUILayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        Vec2 location = touch->getLocation();
        Rect padPickRect = this->m_padPick->getBoundingBox();
        if (padPickRect.containsPoint(location)) {
            
            if (location.x > _defaultPickPos.x + this->m_padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x + this->m_padPick->getContentSize().width / 2;
            } else if (location.x < _defaultPickPos.x - this->m_padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x - this->m_padPick->getContentSize().width / 2;
            }
            
            if (location.y > _defaultPickPos.y + this->m_padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y + this->m_padPick->getContentSize().height / 2;
            } else if (location.y < _defaultPickPos.y - this->m_padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y - this->m_padPick->getContentSize().height / 2;
            }
            
            this->m_padPick->setPosition(location);
        }
        iterator++;
    }
    return;
}


/**
    ドラッグ時に呼び出される
 */
void StageLeftUILayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Rect rect = Rect(0.0f, 0.0f, visibleSize.width - SIDE_BAR_WIDTH, visibleSize.height);
        if (rect.containsPoint(location)) {
            if (location.x > _defaultPickPos.x + this->m_padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x + this->m_padPick->getContentSize().width / 2;
            } else if (location.x < _defaultPickPos.x - this->m_padPick->getContentSize().width / 2) {
                location.x = _defaultPickPos.x - this->m_padPick->getContentSize().width / 2;
            }
            
            if (location.y > _defaultPickPos.y + this->m_padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y + this->m_padPick->getContentSize().height / 2;
            } else if (location.y < _defaultPickPos.y - this->m_padPick->getContentSize().height / 2) {
                location.y = _defaultPickPos.y - this->m_padPick->getContentSize().height / 2;
            }
        this->m_padPick->setPosition(location);
        }
        
        iterator++;
    }
    return;
}


/**
    タッチ終了時に呼び出される
 */
void StageLeftUILayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    this->m_padPick->setPosition(_defaultPickPos);
}


#pragma mark -
#pragma mark Getter
/**
     バーチャルパッドの状態を返却する
 
     @return バーチャルパッドの向き
 */
::padState StageLeftUILayer::padState()
{
    if (_defaultPickPos == this->m_padPick->getPosition()) {
        return ::padNone;
    }
    
    double degree = this->degreeFromVec2(_defaultPickPos, this->m_padPick->getPosition());
    
    if (degree > 45.0 && degree <= 135.0) {
        return ::padUp;
    } else if ((degree >= 0 && degree <= 45.0) || (degree <= 0 && degree > -45.0)) {
        return ::padRight;
    } else if (degree <= -45.0 && degree > -135.0) {
        return ::padDown;
    } else if ((degree <= -135.0 && degree >= -180.0) || (degree > 135 && degree <= 180.0)) {
        return ::padLeft;
    }
    
    return ::padNone;
}


#pragma mark -
/**
     2点の座標から角度を計算して返す
 
     @param posA 1つ目の点の座標
     @param posB 2つ目の点の座標
     @return 角度
 */
double StageLeftUILayer::degreeFromVec2(Vec2 posA, Vec2 posB)
{
    double radian = atan2(posB.y - posA.y, posB.x - posA.x);
    double degree = radian * 180.0 / M_PI;
    return degree;
}


#pragma mark -
#pragma mark GameEvent
/**
    プレイヤーが被弾した
 
    @param i 残りHP
 */
void StageLeftUILayer::heartOff(int i)
{
    if (i < 0) {
        return;
    }
    this->m_heartes.at(i)->setVisible(false);
}
