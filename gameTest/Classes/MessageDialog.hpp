//
//  MessageDialog.hpp
//  gameTest-mobile
//
//  Created by agenda_tanno on 2018/12/07.
//

#ifndef MessageDialog_hpp
#define MessageDialog_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIScale9Sprite.h"

class MessageDialog : public Node
{
    ui::Scale9Sprite* frame = nullptr;
    Sprite* finishArrow;
    
public:
    MessageDialog() {};
    ~MessageDialog();
    virtual bool init(const int frameWidth, const int frameHeight);
    static MessageDialog* create(const int frameWidth, const int frameHeight);
};

#endif /* MessageDialog_hpp */
