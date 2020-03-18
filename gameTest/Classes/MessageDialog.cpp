//
//  MessageDialog.cpp
//  gameTest-mobile
//
//  Created by agenda_tanno on 2018/12/07.
//

#include "MessageDialog.hpp"
#include "StringUtil.h"
#include "Const.hpp"
#include "StageSceneBase.hpp"

const float INTERVAL = 0.1f; // 文字と文字を表示する間隔
const int LABEL_MARGIN = 30; // 表示するラベルの間隔

#pragma mark -
#pragma mark init
/**
    createメソッド
 
    @param frameSize フレームサイズ
    @return メッセージダイアログ
 */
MessageDialog* MessageDialog::create(const Size frameSize)
{
    MessageDialog *pRet = new(std::nothrow) MessageDialog();
    if (pRet && pRet->init(frameSize)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}


/**
    初期化処理
 
    @param frameSize フレームサイズ
 */
bool MessageDialog::init(const Size frameSize)
{    
    if (!Node::init()) {
        return false;
    }
    
    this->initFrame(frameSize);
    this->initFinishArrow();
    this->messageIndex = 0;
    
    this->m_isVisible = false;
    
    
    return true;
}


/**
    フレームの初期化
 */
void MessageDialog::initFrame(const Size frameSize)
{
    Rect outerRect(0, 0, 24, 24);
    Rect innerRect(7, 7, 10, 10);
    this->frame = ui::Scale9Sprite::create("frame.png", outerRect, innerRect);
    this->frame->setAnchorPoint(Vec2(0.5f, 0));
    this->frame->setContentSize(Size(frameSize.width, frameSize.height));
    this->frame->getTexture()->setAliasTexParameters();
    this->addChild(this->frame);
}


/**
    文字送り矢印の初期化
 */
void MessageDialog::initFinishArrow()
{
    this->finishArrow = Sprite::create("arrow.png");
    this->frame->setAnchorPoint(Vec2(0.5f, 0));
    this->finishArrow->setPosition(0, LABEL_MARGIN);
    this->finishArrow->setOpacity(0);
    this->addChild(this->finishArrow);
}


/**
    デストラクタ
 */
MessageDialog::~MessageDialog() {
    this->removeAllChildrenWithCleanup(true);
}


#pragma mark -
/**
    1メッセージの表示を開始する
 */
void MessageDialog::start() {
    this->prepareLabel();
    this->isSending = true;
    this->scheduleUpdate();
}


#pragma mark -
#pragma mark Label
/**
    表示するラベルを準備
 */
void MessageDialog::prepareLabel()
{
    // メッセージの状態をリセット
    this->resetMessage();
    
    // 次に表示するメッセージの選択
    std::string message = this->messageList.at(messageIndex++);
    
    // フラグを設定
    // プレイヤー入力が必要
    if(message.back() == '?') {
        this->isQuestion = true;
    }
    // 2択選択が必要
    else if(message.back() == '$') {
        message.pop_back();
        this->isYesNo = true;
    }
    
    // ラベルを作成
    this->label = this->createMessageLabel(message);
    this->label->setCameraMask((unsigned short)CameraFlag::USER1);
    this->frame->addChild(this->label);
}


/**
    表示用のラベルを作成する
 
    @param message ラベルにする文字列
    @return 作成したラベル
 */
Label* MessageDialog::createMessageLabel(const std::string &message)
{
    Label *label = Label::createWithTTF(message, "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    label->getFontAtlas()->setAliasTexParameters();
    label->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 外側のフレームに合わせて位置とサイズを調整
    label->setPosition(LABEL_MARGIN, this->frame->getContentSize().height - LABEL_MARGIN);
    label->setWidth(this->frame->getContentSize().width - (LABEL_MARGIN * 2));
    label->setHeight(this->frame->getContentSize().height - (LABEL_MARGIN * 2));
    // 文字を透明に設定
    label->setOpacity(0);
    // 行の高さを設定
    label->setLineHeight(label->getLineHeight() * 1.5f);
    return label;
}


#pragma mark -
#pragma mark Message
/**
    メッセージの状態を初期化する
 */
void MessageDialog::resetMessage()
{
    if (this->label != nullptr) {
        this->label->removeFromParentAndCleanup(true);
    }
    if (this->editBox != nullptr) {
        this->editBox->removeFromParentAndCleanup(true);
    }
    this->charIndex = 0;
    this->distance = 0;
    this->isSending = false;
    this->isYesNo = false;
}


/**
    メッセージを配列に追加する
 
    @param &message 追加するメッセージ
 */
void MessageDialog::addMessage(const std::string &message)
{
    this->messageList.push_back(message);
}


#pragma mark -
#pragma mark Update
/**
    定期処理
    経過時間に応じて文字送りを実行する
 */
void MessageDialog::update(float delta)
{
    // 経過時間をインクリメント
    this->distance += delta;
    // インターバル毎に1文字ずつ表示していく
    this->displayCharAtInterval();
    
    // メッセージの最後まで表示したら、文字送りを停止する
    if (this->charIndex >= this->label->getStringLength()) {
        this->isSending = false;
        this->unscheduleUpdate();
        
        if(this->isQuestion && this->editBox == nullptr) {
            this->createEditBox();
        } else if(this->isYesNo) {
            this->createYesNo();
        } else {
            this->startArrowBlink();
        }
    }
}


/**
    一定時間経過毎に、1文字づつラベルを表示する
 */
void MessageDialog::displayCharAtInterval()
{
    // 前の文字を表示してから0.1秒以上経過していなければ何もしない
    if (this->distance < INTERVAL) {
        return;
    }
    
    // 1文字づつ表示していく
    Sprite *charSprite = this->label->getLetter(this->charIndex);
    if (charSprite != nullptr) {
        charSprite->setOpacity(255);
    }
    this->distance = 0;
    this->charIndex++;
}


/**
    Yes/No選択肢を生成する
 */
void MessageDialog::createYesNo()
{
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
    
    // 選択の監視
    schedule(schedule_selector(MessageDialog::updateChoice), 0.1f);
}


/**
    ユーザーの選択の更新を行う
 */
void MessageDialog::updateChoice(float frame)
{
    StageSceneBase *parent = (StageSceneBase*)this->getParent();
    ::padState padState = parent->padState();
    if (padState == padLeft) {
        this->selectChoice(true);
    } else if (padState == padRight) {
        this->selectChoice(false);
    }
}


/**
    プレイヤーの選択に合わせて、矢印の位置を変更する
 
    @param choice プレーヤーの選択
 */
void MessageDialog::selectChoice(bool choice)
{
    if(choice) {
        this->userChoice = true;
        this->userChoiceArrow->setPosition(LABEL_MARGIN, this->label->getHeight() - (LABEL_MARGIN * 2));
    } else {
        this->userChoice = false;
        this->userChoiceArrow->setPosition(this->frame->getContentSize().width / 2, this->label->getHeight() - (LABEL_MARGIN * 2));
    }
}


/**
    EditBoxを生成する
 */
void MessageDialog::createEditBox()
{
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
void MessageDialog::startArrowBlink()
{
    // 点滅用の繰り返しアニメーション
    auto blink = Sequence::create(
                                  DelayTime::create(0.1f),
                                  CallFunc::create([this]() { this->finishArrow->setOpacity(255); }),
                                  DelayTime::create(0.3f),
                                  CallFunc::create([this]() { this->finishArrow->setOpacity(0); }),
                                  DelayTime::create(0.2f),
                                  nullptr
                                  );
    this->finishArrow->runAction(RepeatForever::create(blink));
}


/**
    文字送り完了矢印の点滅を終了する
 */
void MessageDialog::stopAllowBlink()
{
    this->finishArrow->stopAllActions();
    this->finishArrow->setOpacity(0);
}


/**
 */
void MessageDialog::next() {
    // 最後のメッセージまで進んでいれば終了する
    if (this->isViewedAllMessage()) {
        this->startArrowBlink();
        this->closeSelf();
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
    自身を閉じる
 */
void MessageDialog::closeSelf()
{
    this->runAction(
                    Sequence::create(
                                     ScaleTo::create(0.1f, 0, 0.05f, 1),
                                     ScaleTo::create(0.1f, 1, 0.0f, 0.05f),
                                     nullptr
                                     )
                    );
    this->messageIndex = 0;
    this->messageList.clear();
    this->messageList.shrink_to_fit();
    this->m_isVisible = false;
}


/**
    文字送り完了ハンドラをセットする
 */
void MessageDialog::setCompleteAction(std::function<void()> completedAction) {
    this->completedAction = completedAction;
}


/**
    メッセージを全部表示済みかどうか
 */
bool MessageDialog::isViewedAllMessage() {
    return !this->isSending && this->messageIndex >= this->messageList.size();
}
