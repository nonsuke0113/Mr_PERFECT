//
//  AStarNode.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/11.
//

#include "AStarNode.hpp"
#include "AStarUtils.hpp"


#pragma mark -
#pragma mark init
/**
     AStarNodeのcreateメソッド
 
     @param pos 座標
     @param goalPos 目的地座標
     @param parent 親ノード
     @return AStarNode
 */
AStarNode* AStarNode::create(const Vec2 pos, const Vec2 goalPos, AStarNode* parent)
{
    AStarNode *ref = new (std::nothrow) AStarNode();
    if (ref && ref->init(pos, goalPos, parent))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}


/**
     初期化処理
 
     @param pos 座標
     @param goalPos 目的地座標
     @param parent 親ノード
 */
bool AStarNode::init(const Vec2 pos, const Vec2 goalPos, AStarNode* parent)
{
    this->pos = pos;
    this->eCost = AStarUtils::calculateECost(pos, goalPos);
    this->aCost = parent == nullptr ? 0 : parent->aCost + 1;
    this->parentNode = parent;
    
    return true;
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
