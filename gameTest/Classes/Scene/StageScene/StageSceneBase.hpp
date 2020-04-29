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
#include "GameConst.hpp"
#include "PlayerSprite.hpp"
#include "EnemySprite.hpp"
#include "MessageDialogController.hpp"
#include "AdMobHelper.h"
#include "StageUILayer.hpp"
#include "ResultInfo.hpp"

class StageSceneBase : public Scene
{
private:
    void initCamera();
    void initUI();
    void saveScore();
    void updateTime();
    void updatePlayerDirection();
    void updatePosition();
    void updateCameraPosition();
    
protected:
    /// ゲームの状態
    GameState m_state;
    /// ステージ番号
    int m_stageNum;
    /// 敵がプレイヤーを発見した回数
    int m_enemyFoundPlayerCount;
    /// スクロール用カメラ
    Camera *m_camera;
    /// メッセージダイアログコントローラー
    MessageDialogController *m_mdController;
    /// UIレイヤー
    StageUILayer *m_uiLayer;
    /// リザルト用の情報
    ResultInfo *m_resultInfo;
    /// スコア基準値
    ::scoreStandard m_scoreStandard;
    
    virtual void initMap();
    virtual void initCharactors();
    virtual void initScoreStandard();
    virtual void gameStart();
    void gamePause();
    void allNodeUnschedule();
    virtual void touchA();
    virtual void touchB();
    void playerKnockWall();
    virtual void stageClear();
    void setupResult();
    virtual void update(float delta);
    virtual void checkState();
    
public:
    /// 経過時間
    float m_time;
    /// MAP
    TMXTiledMap *m_map;
    /// 操作キャラクター
    PlayerSprite *m_player;
    
    static StageSceneBase *createScene(int stageNum);
    virtual bool init(int stageNum);
    ::padState padState();
    Vector<GameSpriteBase*> gameSpriteVector();
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
