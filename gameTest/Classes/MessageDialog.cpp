//
//  MessageDialog.cpp
//  gameTest-mobile
//
//  Created by agenda_tanno on 2018/12/07.
//

#include "MessageDialog.hpp"
#include "StringUtil.h"

/**
 */
void MessageDialog::prepareLabel()
{
    if (this->label != nullptr) {
        this->label->removeFromParentAndCleanup(true);
    }
    
    this->charIndex = 0;
    
    // 次の表示するメッセージの選択
    this->message = this->messageList.at(messageIndex++);
    
    // 長さを取得
    this->messageLength = StringUtil::lenUtf8(this->message);
    
    // ラベルを作成
    this->label = Label::createWithTTF(this->message, "fonts/PixelMplus12-Regular.ttf", 40);
    // アンチエイリアスをOFF
    this->label->getFontAtlas()->setAliasTexParameters();
    this->label->setAnchorPoint(Vec2(0.0f, 0.0f));
    // 外側のフレームに合わせて位置とサイズを調整
    this->label->setPosition(LABEL_MARGIN,
                             frame->getContentSize().height * frame->getScaleY() / 2);
    this->label->setWidth(frame->getContentSize().width - LABEL_MARGIN);
    this->label->setHeight(frame->getContentSize().height - LABEL_MARGIN);
    
    // 文字を透明に設定
    this->label->setOpacity(0);
    // 行の高さを設定
    this->label->setLineHeight(this->label->getLineHeight() * 1.5f);
    
    this->frame->addChild(this->label);
}

void MessageDialog::addMessage(const std::string &message)
{
    this->messageList.push_back(message);
}

/**
 */
void MessageDialog::start()
{
    this->prepareLabel();
    this->isSending = true;
    this->scheduleUpdate();
}

/**
 */
void MessageDialog::update(float delta)
{
    this->distance += delta;
    
    if (this->distance > this->interval)
    {
        Sprite* sp = this->label->getLetter(this->charIndex);
        sp->setOpacity(255);
        
        this->distance = 0;
        this->charIndex++;
    }
    
    if (this->charIndex >= this->messageLength)
    {
        this->isSending = false;
        this->unscheduleUpdate();
        this->completedAction();
//        this->startArrowBlink();
    }
}

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
    this->frame->setAnchorPoint(Vec2(0.5f,0));
    this->frame->setContentSize(Size(frameWidth, frameHeight));
    this->frame->getTexture()->setAliasTexParameters();
    
    this->addChild(this->frame);
    
    // 文字送り完了の矢印
    
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

void MessageDialog::setCompleteAction(std::function<void()> completedAction)
{
    this->completedAction = completedAction;
}
