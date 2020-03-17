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

// メッセージの種類
typedef enum {
    none,
    nomal,
    failed
} messageType;

class MessageDialogController : public Ref
{
protected:
    void initMessageDialog();
    
public:
    MessageDialog* m_dialog; // メッセージダイアログ
    
    static MessageDialogController* create();
    virtual bool init();
    
};

#endif /* MessageDialogController_hpp */
