//
//  AStarNode.hpp
//  gameTest-mobile
//
//  経路探索用アルゴリズムA*で使用するノード
//
//  Created by 丹野健介 on 2020/02/11.
//

#ifndef AStarNode_hpp
#define AStarNode_hpp

USING_NS_CC;

#include "cocos2d.h"
#include <vector>

class AStarNode : public Ref
{
protected:
    
public:
    /// ワールド座標
    Vec2 m_pos;
    /// 推定(estimated)コスト。このノードから、ゴールノードまでの最短距離。
    float m_eCost;
    /// 実(actual)コスト。スタートノードからの距離+eコスト。
    float m_aCost;
    /// 親のノード。
    AStarNode *m_parentNode;
    
    static AStarNode* create(const Vec2 pos, const Vec2 goalPos, AStarNode* parent);
    virtual bool init(const Vec2 pos, const Vec2 goalPos, AStarNode* parent);
    std::vector<Vec2> shortestRouteStack();
    
};

#endif /* AStarNode_hpp */
