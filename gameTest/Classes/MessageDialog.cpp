//
//  MessageDialog.cpp
//  gameTest-mobile
//
//  Created by agenda_tanno on 2018/12/07.
//

#include "MessageDialog.hpp"

bool MessageDialog::init(const int frameWidth, const int frameHeight)
{
    if (!Node::init())
    {
        return false;
    }
    
    // 外枠の準備
    const Rect outerRect(0, 0, 24, 24);
    const Rect innerRect(7, 7, 10, 10);
    
    this->frame = ui::Scale9Sprite::create("frame.png", outerRect, innerRect);
    this->frame->setAnchorPoint(Vec2(0,0));
    this->frame->setContentSize(Size(frameWidth, frameHeight));
    this->frame->getTexture()->setAliasTexParameters();
    
    this->addChild(this->frame);
    
    // 文字送り完了の矢印
    this->finishArrow = Sprite::create("arrow.png");
    
    this->finishArrow->setAnchorPoint(Vec2(0,0));
    this->finishArrow->setPosition(0, -1 * frame->getContentSize().height / 2 +
                                   this->finishArrow->getContentSize().height + 8);
    this->finishArrow->setOpacity(0);
    this->addChild(this->finishArrow);
    
    return true;
}

MessageDialog* MessageDialog::create(const int frameWidth, const int frameHeight)
{
    MessageDialog *pRet = new(std::nothrow) MessageDialog();
    if (pRet && pRet->init(frameWidth, frameHeight))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

MessageDialog::~MessageDialog()
{
    this->removeAllChildrenWithCleanup(true);
}
