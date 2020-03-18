//
//  MessageDialog.hpp
//  gameTest-mobile
//
//  メッセージ表示するUIクラス
//
//  Created by agenda_tanno on 2018/12/07.
//

#ifndef MessageDialog_hpp
#define MessageDialog_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIScale9Sprite.h"

class MessageDialog : public Node, public ui::EditBoxDelegate
{
private:
    ui::Scale9Sprite *frame; // メッセージフレーム
    Label *label; // 表示中のメッセージラベル
    ui::EditBox *editBox; // プレイヤー入力用EditView
    Sprite *finishArrow; // 文字送り終了矢印
    bool isQuestion; // プレイヤー入力が必要かどうか
    std::vector<std::string> messageList; // 表示するメッセージのリスト
    bool isSending; // 文字送り中かどうか
    Sprite *userChoiceArrow; // 2択用の矢印画像
    int charIndex; // 現在の文字位置
    float distance; // 前の文字を表示してからの経過時間
    std::function<void()> completedAction = nullptr; // 文字送り完了後のハンドラ
    
    
    void initFrame(const Size frameSize);
    void initFinishArrow();
    
    void prepareLabel();
    void resetMessage();
    Label* createMessageLabel(const std::string &message);
    
    void displayCharAtInterval();
    
    void createYesNo();
    void updateChoice(float frame);
    void createEditBox();
    void startArrowBlink();
    void stopAllowBlink();
    void closeSelf();
    
public:
    std::vector<std::string> answerList;
    bool m_isVisible; // メッセージダイアログが表示されているかどうか
    bool isYesNo = false; // プレイヤー選択の2択が必要かどうか
    bool userChoice = true;

    size_t messageIndex;    // 現在表示中のメッセージのインデックス
    
    static MessageDialog* create(const Size frameSize);
    virtual bool init(const Size frameSize);
    ~MessageDialog();
    void start();
    void next();
    void update(float delta);
    void addMessage(const std::string &message);
    void setCompleteAction(std::function<void()> completedAction);
    void selectChoice(bool choice);
    bool isViewedAllMessage();
    
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox);
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox);
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text);
    virtual void editBoxReturn(ui::EditBox *editBox);
};

#endif /* MessageDialog_hpp */
