//
//  MainGameScene.hpp
//  tannoGame
//
//  Created by 健介 丹野 on 2018/08/18.
//
//

#ifndef MainGameScene_hpp
#define MainGameScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "CharacterSprite.hpp"

class MainGameScene : public Layer
{
public:
    
    TMXTiledMap *pMap;
    Camera* pCamera;
    Sprite *pPlayer;
    CharacterSprite *mob1;
    Point pPlayerMapPoint;
    Label* playerMapPointLabel { nullptr };
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainGameScene);
    // ボタンのタッチイベント
    void touchCrossKeyEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void updatePosition(float frame);
    void updateMob1Position(float frame);
    int checkNextTileGID();
    bool checkNextTileMob();
};

#endif /* MainGameScene_hpp */
