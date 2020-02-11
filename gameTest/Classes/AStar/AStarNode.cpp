//
//  AStarNode.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/11.
//

#include "AStarNode.hpp"
#include "AStarUtils.hpp"


/**
    コンストラクタ
 
    @param pos 座標
    @param goalPos 目的地座標
    @param parent 親ノード
 */
AStarNode::AStarNode(Vec2 pos, Vec2 goalPos, AStarNode *parent)
{
    this->pos = pos;
    this->eCost = AStarUtils::calculateECost(pos, goalPos);
    this->aCost = parent == nullptr ? 0 : parent->aCost + 1;
    this->parentNode = parent;
}


/**
    自身の座標をゴールとする最短経路の配列を返す
 */
std::vector<Vec2> AStarNode::shortestRouteStack()
{
    std::vector<Vec2> routeStack;
    AStarNode *node = this;
    while (node) {
        routeStack.insert(routeStack.begin(), node->pos);
        node = node->parentNode;
    }
    return routeStack;
}
