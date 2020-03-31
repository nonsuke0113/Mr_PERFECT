//
//  MessageDialogController.cpp
//  gameTest-mobile
//
//  Created by agenda_tanno on R 2/03/17.
//

#include "MessageDialogController.hpp"
#include "StageSceneBase.hpp"

#pragma mark -
#pragma mark Init
/**
    MessageDialogControllerのcreateメソッド
 
    @return MessageDialogController
 */
MessageDialogController* MessageDialogController::create()
{
    MessageDialogController *ref = new (std::nothrow) MessageDialogController();
    if (ref && ref->init())
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}


/**
    初期化処理
 */
bool MessageDialogController::init()
{
    this->initMessageDialog();
    return true;
}


/**
    メッセージダイアログを初期化
 */
void MessageDialogController::initMessageDialog()
{
    this->m_dialog = MessageDialog::create(Size(640.0f, 200.0f));
    this->m_dialog->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->m_dialog->setPosition(Vec2(568.0f, 0.0f));
    this->m_dialog->setCameraMask((unsigned short)CameraFlag::USER1);
    this->m_dialog->setScale(0.0f);
}


#pragma mark -
#pragma mark Getter
/**
    メッセージダイアログが表示中かどうか
 
    @return メッセージダイアログが表示中かどうか
 */
bool MessageDialogController::isVisibleMessageDialog()
{
    return this->m_dialog->isVisible();
}


#pragma mark -
#pragma mark Setter
/**
    メッセージダイアログにメッセージを追加する
 
    @param messages 追加するメッセージの配列
 */
void MessageDialogController::setMessages(std::vector<std::string> messages)
{
    for (std::string message : messages) {
        this->m_dialog->addMessage(message);
    }
}


/**
    メッセージダイアログにコールバックを設定する
 */
void MessageDialogController::setMessageCallback(std::function<void()> completedAction)
{
    this->m_dialog->setCompleteAction(completedAction);
}


#pragma mark -
/**
    メッセージダイアログを表示する。
    本メソッドを呼び出す前に、必ずm_dialogを呼び出す親にてaddChildするのと、
    メッセージの登録をする必要がある。
 */
void MessageDialogController::displayMessageDialog()
{
    // ダイアログを表示
    this->m_dialog->runAction(
                              Sequence::create(
                                               ScaleTo::create(0.1f, 0, 1, 1),
                                               ScaleTo::create(0.2f, 1, 1, 1),
                                               nullptr
                                               )
                              );
    this->m_dialog->setIsVisible(true);
    // 文字送りを開始
    this->m_dialog->start();
}


/**
    メッセージの文字送りを実行する
 */
void MessageDialogController::next()
{
    this->m_dialog->next();
}


#pragma mark -
#pragma mark CreateMessage
/**
    メッセージダイアログを作成して表示する
 
    @param messages 追加するメッセージの配列
    @param completedAction メッセージ表示後に実行する処理
 */
void MessageDialogController::createMessage(std::vector<std::string> messages, std::function<void()> completedAction)
{
    this->setMessages(messages);
    this->setMessageCallback(completedAction);
    this->displayMessageDialog();
}


/**
    テスト用のメッセージダイアログを作成して表示する
 
    @param tileGID タイルID
 */
void MessageDialogController::createTestMessage(int tileGID)
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("メッセージを開始します。");
    messages.push_back(StringUtils::format("タイルID:%d", tileGID));
    messages.push_back("メッセージを終了します。");
    this->createMessage(messages, NULL);
}


/**
    敵に見つからずに進むミッション開始時のメッセージを作成して表示する
 
    @param completedAction メッセージ表示後に実行する処理
 */
void MessageDialogController::createStartSeekMissonMessage(std::function<void()> completedAction)
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("MISSON:");
    messages.push_back("敵に見つからずに脱出しろ");
    this->createMessage(messages, completedAction);
}


/**
    開始時に、目的は敵を全滅させることであるメッセージを作成して表示する
 
    @param completedAction メッセージ表示後に実行する処理
 */
void MessageDialogController::createStartKillMissonMessage(std::function<void()> completedAction)
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("MISSON:");
    messages.push_back("敵を全滅させろ");
    this->createMessage(messages, completedAction);
}


/**
    開始時に、目的は脱出することであるメッセージを作成して表示する
 
    @param completedAction メッセージ表示後に実行する処理
 */
void MessageDialogController::createStartReachMissonMessage(std::function<void()> completedAction)
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("MISSON:");
    messages.push_back("脱出しろ");
    this->createMessage(messages, completedAction);
}


/**
    ミッション失敗時のメッセージダイアログを作成して表示する
 */
void MessageDialogController::createMissionFailedMessage()
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("コンティニュー？$");
    this->createMessage(messages, [this]() {
        // シーンに通知
        StageSceneBase* mainScene = (StageSceneBase*)this->m_dialog->getParent();
        if (this->m_dialog->userChoice()) {
            mainScene->doContinue();
        } else {
            mainScene->gameover();
        }
    });
}


/**
    敵に見つからないでゴールするミッションにて、敵に見つかってしまった際のメッセージ
 */
void MessageDialogController::createEnemyFoundPlayerMessage()
{
    std::vector<std::string> messages = std::vector<std::string>();
    messages.push_back("「何者だ！」");
    messages.push_back("見つかってしまった...");
    messages.push_back("コンティニュー？$");
    this->createMessage(messages, [this]() {
        // シーンに通知
        StageSceneBase* mainScene = (StageSceneBase*)this->m_dialog->getParent();
        if (this->m_dialog->userChoice()) {
            mainScene->doContinue();
        } else {
            mainScene->gameover();
        }
    });
}
