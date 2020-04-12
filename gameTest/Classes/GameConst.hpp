//
//  GameConst.hpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/12.
//

#ifndef GameConst_hpp
#define GameConst_hpp

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
    int clearStage;
    int clearTime;
    int clearHp;
    int clearFoundCount;
    int timeScore;
    int hpScore;
    int foundScore;
} resultInfo;

/// HP1つあたりのスコア倍率
extern int const HP_SCORE_MAGNIGICATION;

#endif /* GameConst_hpp */
