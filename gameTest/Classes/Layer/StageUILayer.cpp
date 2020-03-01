//
//  StageUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/26.
//

#include "StageUILayer.hpp"
#include "StageSceneBase.hpp"

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

    // 左サイドバー
    this->leftLayer = StageLeftUILayer::create();
    this->leftLayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->leftLayer->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(this->leftLayer);
    
    // 右サイドバー
    this->rightLayer = StageRightUILayer::create();
    this->rightLayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->rightLayer->setPosition(Vec2(888.0f, 0.0f));
    this->addChild(this->rightLayer);
    
    return true;
}


#pragma mark -
/**
    バーチャルパッドの状態を返却する
 
    @return バーチャルパッドの向き
 */
::padState StageUILayer::padState()
{
    return this->leftLayer->padState();
}


/**
    Aボタン押下時のイベント
 */
void StageUILayer::touchAEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // 親に通知する
    StageSceneBase *parent = (StageSceneBase*)this->getParent();
    parent->touchAEvent(pSender, type);
}


/**
    Bボタン押下時のイベント
 */
void StageUILayer::touchBEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    // 親に通知する
    StageSceneBase *parent = (StageSceneBase*)this->getParent();
    parent->touchBEvent(pSender, type);
}


/**
    プレイヤーが被弾した
 
    @param i 残りHP
 */
void StageUILayer::heartOff(int i)
{
    this->leftLayer->heartOff(i);
}
