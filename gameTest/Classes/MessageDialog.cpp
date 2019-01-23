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
    this->label->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 外側のフレームに合わせて位置とサイズを調整
    this->label->setPosition(LABEL_MARGIN, frame->getContentSize().height - LABEL_MARGIN);
    this->label->setWidth(frame->getContentSize().width - (LABEL_MARGIN*2));
    this->label->setHeight(frame->getContentSize().height - (LABEL_MARGIN*2));

    // 文字を透明に設定
    this->label->setOpacity(0);
    // 行の高さを設定
    this->label->setLineHeight(this->label->getLineHeight() * 1.5f);
    
    this->label->setCameraMask((unsigned short)CameraFlag::USER1);
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
        this->startArrowBlink();
    }
}

/**
 */
void MessageDialog::startArrowBlink()
{
    // 点滅用の繰り返しアニメーション
    auto blink = Sequence::create(
                                  DelayTime::create(0.1f),
                                  CallFunc::create([this]() { this->finishArrow->setOpacity(255); }),
                                  DelayTime::create(0.3f),
                                  CallFunc::create([this]() { this->finishArrow->setOpacity(0); }),
                                  DelayTime::create(0.2f),
                                  nullptr);
    
    this->finishArrow->runAction(RepeatForever::create(blink));
}

/**
 */
void MessageDialog::stopAllowBlink()
{
    this->finishArrow->stopAllActions();
    this->finishArrow->setOpacity(0);
}

/**
 */
void MessageDialog::next()
{
    // 最後の最後まで進んでたら終了
    if (!this->isSending && this->messageIndex >= this->messageList.size())
    {
        this->startArrowBlink();
        
        if (this->completedAction != nullptr)
        {
            this->completedAction(); // ハンドラが有ったら通知
        }
        
        return;
    }
    
    // 文字送り中なら最後まで表示
    if (this->isSending)
    {
        // ループを停止して残りを全部表示
        this->unscheduleUpdate();
        this->label->setOpacity(255);
        
        this->isSending = false;
        
        this->startArrowBlink();
    }
    else
    {
        this->start();
        this->stopAllowBlink();
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
    this->finishArrow = Sprite::create("arrow.png");
    this->frame->setAnchorPoint(Vec2(0.5f,0));
    this->finishArrow->setPosition(0, LABEL_MARGIN);
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

void MessageDialog::setCompleteAction(std::function<void()> completedAction)
{
    this->completedAction = completedAction;
}
