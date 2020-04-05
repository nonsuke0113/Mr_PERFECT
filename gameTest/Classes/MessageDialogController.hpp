//
//  MessageDialogController.hpp
//  gameTest-mobile
//
//  メッセージダイアログのコントローラー
//
//  Created by agenda_tanno on R 2/03/17.
//

#ifndef MessageDialogController_hpp
#define MessageDialogController_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "MessageDialog.hpp"
#include <vector>

class MessageDialogController : public Ref
{
protected:
    void initMessageDialog();
    void createMessage(std::vector<std::string> messages, std::function<void()> completedAction);
    
public:
    MessageDialog* m_dialog; // メッセージダイアログ
    
    static MessageDialogController* create();
    virtual bool init();
    bool isVisibleMessageDialog();
    void setMessages(std::vector<std::string> messages);
    void setMessageCallback(std::function<void()> completedAction);
    void displayMessageDialog();
    void next();
    void createTestMessage(int tileGID);
    void createStartSeekMissonMessage(std::function<void()> completedAction);
    void createStartKillMissonMessage(std::function<void()> completedAction);
    void createStartReachMissonMessage(std::function<void()> completedAction);
    void createMissionFailedMessage();
    void createEnemyFoundPlayerMessage();
    void createPauseMessage();
};

#endif /* MessageDialogController_hpp */
