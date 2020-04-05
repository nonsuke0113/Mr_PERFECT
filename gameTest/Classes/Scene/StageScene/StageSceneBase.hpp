//
//  StageSceneBase.hpp
//  gameTest-mobile
//
//  ゲームの1ステージシーンの基底クラス
//
//  Created by 丹野健介 on 2019/12/17.
//

#ifndef StageSceneBase_hpp
#define StageSceneBase_hpp

USING_NS_CC;

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayerSprite.hpp"
#include "EnemySprite.hpp"
#include "MessageDialogController.hpp"
#include "AdMobHelper.h"
#include "StageUILayer.hpp"


// クリアランク
typedef enum {
    A,
    B,
    C
} clearRank;

// リザルト情報
typedef struct {
    int clearStage;
    int clearTime;
    int clearHp;
    int clearFoundCount;
    int timeScore;
    int hpScore;
    int foundScore;
} resultInfo;


class StageSceneBase : public Scene
{
private:
    void initCamera();
    void initUI();
    void updateTime();
    void updatePlayerDirection();
    void updatePosition();
    void updateCameraPosition();
    
protected:
    bool m_pause; // 一時停止中かどうか
    float m_shootBulletInterval; // 弾丸を撃てない間隔
    int m_enemyFoundPlayerCount; // 敵がプレイヤーを発見した回数
    Camera *m_camera; // スクロール用カメラ
    MessageDialogController *m_mdController; // メッセージダイアログコントローラー
    StageUILayer *m_uiLayer; // UIレイヤー
    ::resultInfo m_resultInfo; // リザルト用の情報
    
    virtual void initMap();
    virtual void initCharactors();
    virtual void gameStart();
    void gamePause();
    void allNodeUnschedule();
    virtual void touchA();
    virtual void touchB();
    void playerKnockWall();
    virtual void stageClear();
    virtual void setupResult();
    virtual void update(float delta);
    virtual void checkState();
    
public:
    float m_time; // 経過時間
    TMXTiledMap *m_map; // MAP
    PlayerSprite *m_player; // 操作キャラクター
    
    static StageSceneBase *createScene();
    virtual bool init();
    ::padState padState();
    Vector<CharacterSprite*> charactersVector();
    Vector<EnemySprite*> enemysVector();
    void touchAEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchBEvent(Ref *pSender, ui::Widget::TouchEventType type);
    void touchPauseEvent(Ref *pSender, ui::Widget::TouchEventType type);
    virtual void doContinue();
    void gameover();
    void gameResume();
    void backMissionSelectScene();
    void missionFailed();
    virtual void enemyFoundPlayer();
    void heartOff(int i);
    
};

#endif /* StageSceneBase_hpp */
