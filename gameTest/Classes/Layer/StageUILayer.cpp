//
//  StageUILayer.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/26.
//

#include "StageUILayer.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark Init
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
    this->m_leftLayer = StageLeftUILayer::create();
    this->m_leftLayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_leftLayer->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(this->m_leftLayer);
    
    // 右サイドバー
    this->m_rightLayer = StageRightUILayer::create();
    this->m_rightLayer->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_rightLayer->setPosition(Vec2(888.0f, 0.0f));
    this->addChild(this->m_rightLayer);
    
    return true;
}


#pragma mark -
#pragma mark Getter
/**
    バーチャルパッドの状態を返却する
 
    @return バーチャルパッドの向き
 */
::padState StageUILayer::padState()
{
    return this->m_leftLayer->padState();
}


#pragma mark -
#pragma mark ButtonEvent
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


#pragma mark -
#pragma mark GameEvent
/**
    プレイヤーが被弾した
 
    @param i 残りHP
 */
void StageUILayer::heartOff(int i)
{
    this->m_leftLayer->heartOff(i);
}


#pragma mark -
#pragma mark Update
/**
    経過時間ラベルを更新する
 
    @param time 経過時間
 */
void StageUILayer::updateTime(float time)
{
    this->m_rightLayer->updateTime(time);
}
