//
//  MessageDialog.cpp
//  gameTest-mobile
//
//  Created by agenda_tanno on 2018/12/07.
//

#include "MessageDialog.hpp"
#include "StringUtil.h"
#include "Const.hpp"

/**
    表示するラベルを作成
 */
void MessageDialog::prepareLabel() {
    
    if (this->label != nullptr) {
        this->label->removeFromParentAndCleanup(true);
    }
    if (this->editBox != nullptr) {
        this->editBox->removeFromParentAndCleanup(true);
    }
    
    this->charIndex = 0;
    
    // 次の表示するメッセージの選択
    this->message = this->messageList.at(messageIndex++);
    
    // ユーザーの回答に応じて、メッセージの内容を変換する
    if(this->message.find("*") != -1) {
        int replaceIndex = (int)this->message[this->message.find("*")+1] - (int)'0';
        if(!(replaceIndex > answerList.size())) {
            this->message.replace(this->message.find("*"), 2, answerList[replaceIndex-1]);
        }
    }
    
    // 問いかけフラグを設定
    if(this->message.back() == '?') {
        this->isQuestion = true;
    } else if(this->message.back() == '$') {
        this->message.pop_back();
        this->isYesNo = true;
    }
    
    // 表示するメッセージの長さ(文字数)を取得
    this->messageLength = StringUtil::lenUtf8(this->message);
    
    // ラベルを作成
    this->label = Label::createWithTTF(this->message, "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    this->label->getFontAtlas()->setAliasTexParameters();
    this->label->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 外側のフレームに合わせて位置とサイズを調整
    this->label->setPosition(LABEL_MARGIN, frame->getContentSize().height - LABEL_MARGIN);
    this->label->setWidth(this->frame->getContentSize().width - (LABEL_MARGIN*2));
    this->label->setHeight(this->frame->getContentSize().height - (LABEL_MARGIN*2));

    // 文字を透明に設定
    this->label->setOpacity(0);
    // 行の高さを設定
    this->label->setLineHeight(this->label->getLineHeight() * 1.5f);
    
    this->label->setCameraMask((unsigned short)CameraFlag::USER1);
    this->frame->addChild(this->label);
}


/**
    メッセージを配列に追加する
 
    @param &message 追加するメッセージ
 */
void MessageDialog::addMessage(const std::string &message) {
    this->messageList.push_back(message);
}

/**
    メッセージの表示を開始する
 */
void MessageDialog::start() {
    this->prepareLabel();
    this->isSending = true;
    this->scheduleUpdate();
}


/**
    経過時間に応じて文字送りを実行
 
    @param delta 
 */
void MessageDialog::update(float delta) {
    
    this->distance += delta;
    
    if (this->distance > this->interval) {
        // 1文字ずつ表示していく
        Sprite* sp = this->label->getLetter(this->charIndex);
        sp->setOpacity(255);
        this->distance = 0;
        this->charIndex++;
    }
    
    // メッセージの最後まで表示したら、文字送りを停止する
    if (this->charIndex >= this->messageLength) {
        this->isSending = false;
        this->unscheduleUpdate();
        this->startArrowBlink();
        
        if(this->isQuestion && this->editBox == nullptr) {
            this->createEditBox();
        } else if(this->isYesNo) {
            this->createYesNo();
        }
        
    }
}


/**
    Yes/No選択肢を生成する
 */
void MessageDialog::createYesNo() {
    
    this->isYesNo = true;
    
    // Yesラベルを作成
    Label* yesLabel = Label::createWithTTF("はい", "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    yesLabel->getFontAtlas()->setAliasTexParameters();
    yesLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 表示中のラベルに合わせて位置とサイズを調整
    yesLabel->setPosition(LABEL_MARGIN*2, this->label->getHeight() - LABEL_MARGIN);
    yesLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->frame->addChild(yesLabel);
    
    // Noラベルを作成
    Label* noLabel = Label::createWithTTF("いいえ", "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    noLabel->getFontAtlas()->setAliasTexParameters();
    noLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 表示中のラベルに合わせて位置とサイズを調整
    noLabel->setPosition(this->frame->getContentSize().width/2 + LABEL_MARGIN, this->label->getHeight() - LABEL_MARGIN);
    noLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->frame->addChild(noLabel);
    
    // ユーザー選択の矢印を作成
    this->userChoiceArrow = Sprite::create("arrow.png");
    this->userChoiceArrow->setScale(2.0f);
    this->userChoiceArrow->setRotation(-90);
    this->userChoiceArrow->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->userChoiceArrow->setPosition(LABEL_MARGIN, this->label->getHeight() - (LABEL_MARGIN*2));
    this->userChoiceArrow->setCameraMask((unsigned short)CameraFlag::USER1);
    this->frame->addChild(this->userChoiceArrow);
}


/**
 */
void MessageDialog::selectChoice(bool choice) {
    if(choice) {
        this->userChoice = true;
        this->userChoiceArrow->setPosition(LABEL_MARGIN, this->label->getHeight() - (LABEL_MARGIN*2));
    } else {
        this->userChoice = true;
        this->userChoiceArrow->setPosition(this->frame->getContentSize().width/2, this->label->getHeight() - (LABEL_MARGIN*2));
    }
    
}



/**
    EditBoxを生成する
 */
void MessageDialog::createEditBox() {
    
    this->editBox = ui::EditBox::create(Size(480, 50), ui::Scale9Sprite::create("side_test.png"));
    this->editBox->setFont("fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    this->editBox->setAnchorPoint(Vec2(0.5f,0));
    this->editBox->setPosition(Vec2(0.0f, LABEL_MARGIN*2));
    this->editBox->setPlaceHolder("ここに入力してください");
    this->editBox->setPlaceholderFontColor(Color3B::GRAY);
    this->editBox->setPlaceholderFontSize(MESSAGE_FONT_SIZE);
    this->editBox->setFontColor(Color3B::BLACK);
    this->editBox->setMaxLength(10);
    this->editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->editBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->editBox->setDelegate(this);
    this->editBox->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(this->editBox);
}

void MessageDialog::editBoxEditingDidBegin(ui::EditBox *editBox) {
}

void MessageDialog::editBoxEditingDidEnd(ui::EditBox *editBox) {
}

void MessageDialog::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
}

void MessageDialog::editBoxReturn(ui::EditBox *editBox) {
}


/**
    文字送り完了矢印の点滅を開始する
 */
void MessageDialog::startArrowBlink() {
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
    文字送り完了矢印の点滅を終了する
 */
void MessageDialog::stopAllowBlink() {
    this->finishArrow->stopAllActions();
    this->finishArrow->setOpacity(0);
}


/**
 */
void MessageDialog::next() {
    // 最後のメッセージまで進んでいれば終了する
    if (!this->isSending && this->messageIndex >= this->messageList.size()) {
        this->startArrowBlink();
        // ハンドラが有れば文字送りの完了を通知
        if (this->completedAction != nullptr) {
            this->completedAction();
        }
        return;
    }

    // 文字送り中なら最後まで表示
    if (this->isSending) {
        // 1文字づつの文字送りを停止して、残りの文字を全部表示
        this->unscheduleUpdate();
        this->label->setOpacity(255);
        this->isSending = false;
        this->startArrowBlink();
        
        // 問いかけメッセージの場合は、EditBoxを生成
        if(this->isQuestion && this->editBox == nullptr) {
            this->createEditBox();
        }
    }
    // それ以外の場合は、次のメッセージの文字送りを開始する
    else {
        if(this->isQuestion) {
            // ユーザーの入力待ちの場合は、文字送りをしない
            if(this->editBox != nullptr && strcmp(this->editBox->getText(), "") != 0) {
                this->isQuestion = false;
                this->answerList.push_back(editBox->getText());
            } else {
                return;
            }
        }
        this->start();
        this->stopAllowBlink();
    }
}


/**
    初期化処理
 
    @param frameWidth
    @param frameHeight
 */
bool MessageDialog::init(const int frameWidth, const int frameHeight) {
    
    if (!Node::init()) {
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
    if (pRet && pRet->init(frameWidth, frameHeight)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

MessageDialog::~MessageDialog() {
    this->removeAllChildrenWithCleanup(true);
}

/**
    文字送り完了ハンドラをセットする
 */
void MessageDialog::setCompleteAction(std::function<void()> completedAction) {
    this->completedAction = completedAction;
}
