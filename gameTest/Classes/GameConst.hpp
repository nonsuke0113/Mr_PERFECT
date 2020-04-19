//
//  GameConst.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/12.
//

#ifndef GameConst_hpp
#define GameConst_hpp

#pragma mark -
#pragma mark Game
/// ゲームの状態
enum class GameState {
    InProgress, // 進行中
    Pause, // 一時停止中
    End // 終了
};

#pragma mark -
#pragma mark UILayout
/// 画面の高さ(pixel)
extern float const VIEW_HEGHT;
/// 画面の幅(pixel)
extern float const VIEW_WIDTH;
/// サイドバーの幅(pixel)
extern float const SIDE_BAR_WIDTH;

#pragma mark -
#pragma mark Tile
/// 1MAP_TILEあたりのサイズ(pixel)
extern float const PER_TILE_SIZE;
/// MAPの高さ(Tile)
extern int const MAP_TILE_HEGHT;
/// MAPの幅(Tile)
extern int const MAP_TILE_WIDTH;

/**
   進入可能なタイルIDかどうかを返す
*/
bool isCanEnterTileGID(int gid);

/**
   壁のタイルIDかどうかを返す
*/
bool isWallTileGID(int gid);

#pragma mark -
#pragma mark GameSprite
/// ゲーム画像の移動速度
extern float const SPRITE_MOVE_SPEED;

#pragma mark -
#pragma mark Charactor
/// キャラクターのアニメーション切り替え速度
extern float const CHARACTER_ANIMATION_SPEED;
/// プレイヤーが銃弾を打てる間隔
extern float const SHOOT_BULLET_INTERVAL;

#pragma mark -
#pragma mark Message
/// メッセージフォントサイズ
extern int const MESSAGE_FONT_SIZE;

#pragma mark -
#pragma mark Result
/// リザルト情報
typedef struct {
    int clearStage; // ステージ情報
    int clearTime; // クリア時間
    int clearHp; // クリア時のHP
    int clearFoundCount; // 敵に見つかった回数
    int timeScore; // タイムスコア
    int hpScore; // HPスコア
    int foundScore; // 発見数スコア
} resultInfo;

/// ステージごとのスコア基準値
typedef struct {
    int timeScoreStandardA; // タイムスコアAの基準値
    int timeScoreStandardB; // タイムスコアBの基準値
    int foundScoreStandardA; // 発見数スコアAの基準値
    int foundScoreStandardB; // 発見数スコアBの基準値
} scoreStandard;

/// HP1つあたりのスコア倍率
extern int const HP_SCORE_MAGNIGICATION;
/// タイムスコアAの基準値を更に上回った際のボーナス(1秒ごと)
extern int const TIME_SCORE_BONUS_PS;
/// トータルスコアPの基準値
extern int const TOTAL_SCORE_P_STANDARD;
/// トータルスコアAの基準値
extern int const TOTAL_SCORE_A_STANDARD;
/// トータルスコアBの基準値
extern int const TOTAL_SCORE_B_STANDARD;
/// 項目別スコアAの基準値
extern int const SCORE_A_STANDARD_BY_ITEM;
/// 項目別スコアBの基準値
extern int const SCORE_B_STANDARD_BY_ITEM;
/// 項目別スコアCの基準値
extern int const SCORE_C_STANDARD_BY_ITEM;

#endif /* GameConst_hpp */
