//
//  AStarNode.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/11.
//

#include "AStarNode.hpp"
#include "AStarUtils.hpp"


#pragma mark -
#pragma mark Init
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
    this->m_pos = pos;
    this->m_eCost = AStarUtils::calculateECost(pos, goalPos);
    this->m_aCost = parent == nullptr ? 0 : parent->m_aCost + 1;
    this->m_parentNode = parent;
    
    return true;
}


#pragma mark -
/**
    自身の座標をゴールとする最短経路の配列を返す
 */
std::vector<Vec2> AStarNode::shortestRouteStack()
{
    std::vector<Vec2> routeStack;
    AStarNode *node = this;
    while (node) {
        routeStack.insert(routeStack.begin(), node->m_pos);
        node = node->m_parentNode;
    }
    return routeStack;
}
