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
    this->m_messageIndex = 0;
    this->m_isVisible = false;
    this->m_completedAction = nullptr;
    
    return true;
}


/**
    フレームの初期化
 */
void MessageDialog::initFrame(const Size frameSize)
{
    Rect outerRect(0, 0, 24, 24);
    Rect innerRect(7, 7, 10, 10);
    this->m_frame = ui::Scale9Sprite::create("frame.png", outerRect, innerRect);
    this->m_frame->setAnchorPoint(Vec2(0.5f, 0));
    this->m_frame->setContentSize(Size(frameSize.width, frameSize.height));
    this->m_frame->getTexture()->setAliasTexParameters();
    this->addChild(this->m_frame);
}


/**
    文字送り矢印の初期化
 */
void MessageDialog::initFinishArrow()
{
    this->m_finishArrow = Sprite::create("arrow.png");
    this->m_frame->setAnchorPoint(Vec2(0.5f, 0));
    this->m_finishArrow->setPosition(0, LABEL_MARGIN);
    this->m_finishArrow->setOpacity(0);
    this->addChild(this->m_finishArrow);
}


/**
    デストラクタ
 */
MessageDialog::~MessageDialog() {
    this->removeAllChildrenWithCleanup(true);
}


/**
    自身を閉じる
 */
void MessageDialog::closeSelf()
{
    this->stopAllowBlink();
    this->runAction(
                    Sequence::create(
                                     ScaleTo::create(0.1f, 0, 0.05f, 1),
                                     ScaleTo::create(0.1f, 1, 0.0f, 0.05f),
                                     nullptr
                                     )
                    );
    this->m_messageIndex = 0;
    this->m_messageList.clear();
    this->m_messageList.shrink_to_fit();
    this->m_isVisible = false;
    
    // ハンドラが有れば文字送りの完了を通知
    if (this->m_completedAction != nullptr) {
        this->m_completedAction();
    }
}


#pragma mark -
#pragma mark Getter
/**
    メッセージダイアログが表示されているかどうか
 
    @return メッセージダイアログが表示されているかどうか
 */
bool MessageDialog::isVisible()
{
    return this->m_isVisible;
}


/**
    はい/いいえ選択肢のプレイヤー選択ゲッター
 
    @param はい/いいえ選択肢にてプレイヤーがどちらを選んだか
 */
bool MessageDialog::userChoice()
{
    return this->m_userChoice;
}


/**
    プレイヤーの入力リスト
 
    @return プレイヤーの入力リスト
 */
std::vector<std::string> MessageDialog::answerList()
{
    return this->m_answerList;
}


#pragma mark -
#pragma mark Setter
/**
    m_isVisibleセッター
 
    @param メッセージダイアログ表示中かどうか
 */
void MessageDialog::setIsVisible(bool isVisible)
{
    this->m_isVisible = isVisible;
}


/**
    文字送り完了ハンドラのセッター
 
    @param 文字送り完了時点で実行する関数のハンドラ
 */
void MessageDialog::setCompleteAction(std::function<void()> completedAction) {
    this->m_completedAction = completedAction;
}


#pragma mark -
#pragma mark Action
/**
    1メッセージの表示を開始する
 */
void MessageDialog::start() {
    this->prepareLabel();
    this->m_isSending = true;
    this->scheduleUpdate();
}


/**
    1メッセージの文字送りを実行する
 */
void MessageDialog::next()
{
    // 最後のメッセージまで進んでいれば終了する
    if (!(this->m_isNeedChoice && this->m_userChoiceArrow == nullptr) &&
        !this->m_isSending &&
        this->m_messageIndex >= this->m_messageList.size())
    {
        this->closeSelf();
        return;
    }
    
    // 文字送り中なら最後まで表示
    if (this->m_isSending) {
        // 1文字づつの文字送りを停止して、残りの文字を全部表示
        this->m_isSending = false;
        this->unscheduleUpdate();
        this->m_label->setOpacity(255);
        this->startArrowBlink();
        
        // 問いかけメッセージの場合は、EditBoxを生成
        if(this->m_isNeedInput && this->m_editBox == nullptr) {
            this->createEditBox();
        }
        // 選択メッセージの場合は、2択選択を表示
        else if (this->m_isNeedChoice) {
            this->createChoice();
        }
    }
    // それ以外の場合は、次のメッセージの文字送りを開始する
    else {
        if(this->m_isNeedInput) {
            // プレイヤーの入力があれば、保持する
            if(this->m_editBox != nullptr && strcmp(this->m_editBox->getText(), "") != 0) {
                this->m_isNeedInput = false;
                this->m_answerList.push_back(this->m_editBox->getText());
            }
            // プレイヤーの入力待ちの場合は、文字送りをしない
            else {
                return;
            }
        }
        this->start();
        this->stopAllowBlink();
    }
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
    std::string message = this->m_messageList.at(m_messageIndex++);
    
    // フラグを設定
    // プレイヤー入力が必要
    if(message.back() == '?') {
        this->m_isNeedInput = true;
    }
    // 2択選択が必要
    else if(message.back() == '$') {
        message.pop_back();
        this->m_isNeedChoice = true;
    }
    
    // ラベルを作成
    this->m_label = this->createMessageLabel(message);
    this->m_label->setCameraMask((unsigned short)CameraFlag::USER1);
    this->m_frame->addChild(this->m_label);
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
    label->setPosition(LABEL_MARGIN, this->m_frame->getContentSize().height - LABEL_MARGIN);
    label->setWidth(this->m_frame->getContentSize().width - (LABEL_MARGIN * 2));
    label->setHeight(this->m_frame->getContentSize().height - (LABEL_MARGIN * 2));
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
    if (this->m_label != nullptr) {
        this->m_label->removeFromParentAndCleanup(true);
    }
    if (this->m_editBox != nullptr) {
        this->m_editBox->removeFromParentAndCleanup(true);
    }
    this->m_charIndex = 0;
    this->m_distance = 0;
    this->m_isSending = false;
    this->m_isNeedInput = false;
    this->m_isNeedChoice = false;
}


/**
    メッセージを配列に追加する
 
    @param &message 追加するメッセージ
 */
void MessageDialog::addMessage(const std::string &message)
{
    this->m_messageList.push_back(message);
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
    this->m_distance += delta;
    // インターバル毎に1文字ずつ表示していく
    this->displayCharAtInterval();
    
    // メッセージの最後まで表示したら、文字送りを停止する
    if (this->m_charIndex >= this->m_label->getStringLength()) {
        this->m_isSending = false;
        this->unscheduleUpdate();
        
        // EditBoxを表示
        if(this->m_isNeedInput && this->m_editBox == nullptr) {
            this->createEditBox();
        }
        // はい/いいえの選択肢を表示
        else if(this->m_isNeedChoice) {
            this->createChoice();
        }
        // 矢印の点滅を開始
        else {
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
    if (this->m_distance < INTERVAL) {
        return;
    }
    
    // 1文字づつ表示していく
    Sprite *charSprite = this->m_label->getLetter(this->m_charIndex);
    if (charSprite != nullptr) {
        charSprite->setOpacity(255);
    }
    this->m_distance = 0;
    this->m_charIndex++;
}


#pragma mark -
#pragma mark Choice
/**
    Yes/No選択肢を生成する
 */
void MessageDialog::createChoice()
{
    // Yesラベルを作成
    Label *yesLabel = Label::createWithTTF("はい", "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    yesLabel->getFontAtlas()->setAliasTexParameters();
    yesLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 表示中のラベルに合わせて位置とサイズを調整
    yesLabel->setPosition(LABEL_MARGIN * 2, this->m_label->getHeight() - LABEL_MARGIN);
    yesLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->m_frame->addChild(yesLabel);
    
    // Noラベルを作成
    Label *noLabel = Label::createWithTTF("いいえ", "fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    // アンチエイリアスをOFF
    noLabel->getFontAtlas()->setAliasTexParameters();
    noLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    // 表示中のラベルに合わせて位置とサイズを調整
    noLabel->setPosition(this->m_frame->getContentSize().width / 2 + LABEL_MARGIN, this->m_label->getHeight() - LABEL_MARGIN);
    noLabel->setCameraMask((unsigned short)CameraFlag::USER1);
    this->m_frame->addChild(noLabel);
    
    // ユーザー選択の矢印を作成
    this->m_userChoiceArrow = Sprite::create("arrow.png");
    this->m_userChoiceArrow->setScale(2.0f);
    this->m_userChoiceArrow->setRotation(-90.0f);
    this->m_userChoiceArrow->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->m_userChoiceArrow->setPosition(LABEL_MARGIN, this->m_label->getHeight() - (LABEL_MARGIN * 2));
    this->m_userChoiceArrow->setCameraMask((unsigned short)CameraFlag::USER1);
    this->m_frame->addChild(this->m_userChoiceArrow);
    
    this->m_userChoice = true;
    
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
        this->m_userChoice = true;
        this->m_userChoiceArrow->setPosition(LABEL_MARGIN, this->m_label->getHeight() - (LABEL_MARGIN * 2));
    } else {
        this->m_userChoice = false;
        this->m_userChoiceArrow->setPosition(this->m_frame->getContentSize().width / 2, this->m_label->getHeight() - (LABEL_MARGIN * 2));
    }
}


#pragma mark -
#pragma mark EditBox
/**
    EditBoxを生成する
 */
void MessageDialog::createEditBox()
{
    this->m_editBox = ui::EditBox::create(Size(480.0f, 50.0f), ui::Scale9Sprite::create("side_test.png"));
    this->m_editBox->setFont("fonts/PixelMplus12-Regular.ttf", MESSAGE_FONT_SIZE);
    this->m_editBox->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->m_editBox->setPosition(Vec2(0.0f, LABEL_MARGIN * 2));
    this->m_editBox->setPlaceHolder("ここに入力してください");
    this->m_editBox->setPlaceholderFontColor(Color3B::GRAY);
    this->m_editBox->setPlaceholderFontSize(MESSAGE_FONT_SIZE);
    this->m_editBox->setFontColor(Color3B::BLACK);
    this->m_editBox->setMaxLength(10);
    this->m_editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->m_editBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->m_editBox->setDelegate(this);
    this->m_editBox->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(this->m_editBox);
}

void MessageDialog::editBoxEditingDidBegin(ui::EditBox *editBox) {
}

void MessageDialog::editBoxEditingDidEnd(ui::EditBox *editBox) {
}

void MessageDialog::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
}

void MessageDialog::editBoxReturn(ui::EditBox *editBox) {
}


#pragma mark -
#pragma mark Arrow
/**
    文字送り完了矢印の点滅を開始する
 */
void MessageDialog::startArrowBlink()
{
    // 点滅用の繰り返しアニメーション
    auto blink = Sequence::create(
                                  DelayTime::create(0.1f),
                                  CallFunc::create([this]() { this->m_finishArrow->setOpacity(255); }),
                                  DelayTime::create(0.3f),
                                  CallFunc::create([this]() { this->m_finishArrow->setOpacity(0); }),
                                  DelayTime::create(0.2f),
                                  nullptr
                                  );
    this->m_finishArrow->runAction(RepeatForever::create(blink));
}


/**
    文字送り完了矢印の点滅を終了する
 */
void MessageDialog::stopAllowBlink()
{
    this->m_finishArrow->stopAllActions();
    this->m_finishArrow->setOpacity(0);
}
