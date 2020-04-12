//
//  GameConst.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/12.
//

#include "GameConst.hpp"

#pragma mark -
#pragma mark UILayout
float const VIEW_HEGHT = 640.0f;
float const VIEW_WIDTH = 1136.0f;
float const SIDE_BAR_WIDTH = 248.0f;

#pragma mark -
#pragma mark Tile
float const PER_TILE_SIZE = 64.0f;
int const MAP_TILE_HEGHT = 30;
int const MAP_TILE_WIDTH = 30;

/**
   進入可能なタイルIDかどうかを返す
*/
bool isCanEnterTileGID(int gid)
{
    return gid == 0 || gid == 3;
}

/**
    壁のタイルIDかどうかを返す
 */
bool isWallTileGID(int gid)
{
    return gid == 1 || gid == 2;
}

#pragma mark -
#pragma mark Charactor
float const CHARACTER_ANIMATION_SPEED = 0.5f;
float const SHOOT_BULLET_INTERVAL = 60.0f;

#pragma mark -
#pragma mark Message
int const MESSAGE_FONT_SIZE = 40;

#pragma mark -
#pragma mark Result
int const HP_SCORE_MAGNIGICATION = 1000;
