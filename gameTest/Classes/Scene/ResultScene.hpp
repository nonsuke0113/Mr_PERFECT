//
//  ResultScene.hpp
//  gameTest-mobile
//
//  リザルトシーン
//
//  Created by 丹野健介 on 2020/03/10.
//

#ifndef ResultScene_hpp
#define ResultScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ResultScene : public Layer
{
private:
        
public:
    static Scene* createScene();
    CREATE_FUNC(ResultScene);
    virtual bool init();
    
};

#endif /* ResultScene_hpp */
