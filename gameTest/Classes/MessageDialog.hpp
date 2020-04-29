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
    /// メッセージフレーム
    ui::Scale9Sprite *m_frame;
    /// 表示中のメッセージラベル
    Label *m_label;
    /// プレイヤー入力用EditView
    ui::EditBox *m_editBox;
    /// 文字送り終了矢印
    Sprite *m_finishArrow;
    /// 2択用の矢印画像
    Sprite *m_userChoiceArrow;
    /// メッセージダイアログが表示されているかどうか
    bool m_isVisible;
    /// プレイヤー入力が必要かどうか
    bool m_isNeedInput;
    /// プレイヤー選択の2択が必要かどうか
    bool m_isNeedChoice;
    /// 文字送り中かどうか
    bool m_isSending;
    /// プレイヤーの選択
    bool m_userChoice;
    /// 表示するメッセージのリスト
    std::vector<std::string> m_messageList;
    /// プレイヤー入力のリスト
    std::vector<std::string> m_answerList;
    /// 現在表示中のメッセージのインデックス
    int m_messageIndex;
    /// 現在の文字位置
    int m_charIndex;
    /// 前の文字を表示してからの経過時間
    float m_distance;
    /// 文字送り完了後のハンドラ
    std::function<void()> m_completedAction;
    
    void initFrame(const Size frameSize);
    void initFinishArrow();
    void closeSelf();
    void prepareLabel();
    Label* createMessageLabel(const std::string &message);
    void resetMessage();
    void update(float delta);
    void displayCharAtInterval();
    void createChoice();
    void updateChoice(float frame);
    void selectChoice(bool choice);
    void createEditBox();
    void startArrowBlink();
    void stopAllowBlink();
    
public:   
    static MessageDialog* create(const Size frameSize);
    virtual bool init(const Size frameSize);
    ~MessageDialog();
    bool isVisible();
    bool userChoice();
    std::vector<std::string> answerList();
    void setIsVisible(bool isVisible);
    void setCompleteAction(std::function<void()> completedAction);
    void start();
    void next();
    void addMessage(const std::string &message);
    virtual void editBoxEditingDidBegin(ui::EditBox *editBox);
    virtual void editBoxEditingDidEnd(ui::EditBox *editBox);
    virtual void editBoxTextChanged(ui::EditBox *editBox, const std::string& text);
    virtual void editBoxReturn(ui::EditBox *editBox);
    
};

#endif /* MessageDialog_hpp */
