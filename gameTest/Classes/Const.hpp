//
//  Const.hpp
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2018/11/28.
//

#ifndef Const_hpp
#define Const_hpp

constexpr float VIEW_HEGHT = 640.0f; // 画面の高さ(pixel)
constexpr float VIEW_WIDTH = 960.0f; // 画面の幅(pixel)
constexpr float SIDE_BAR_WIDTH = 160.0f; // サイドバーの幅(pixel)

constexpr float PER_TILE_SIZE { 32.0f }; // 1MAP_TILEあたりのサイズ(pixel)

constexpr int MAP_TILE_HEGHT = 40; // MAPの高さ(Tile)
constexpr int MAP_TILE_WIDTH = 40; // MAPの幅(Tile)

// 向き
typedef enum {
    character_back,
    character_right,
    character_front,
    character_left
} characterDirectcion;

#endif /* Const_h */
