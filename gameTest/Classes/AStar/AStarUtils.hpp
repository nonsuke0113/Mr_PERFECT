//
//  AStarUtils.hpp
//  gameTest-mobile
//
//  経路探索用アルゴリズムA*用のUtiltiyクラス
//
//  Created by 丹野健介 on 2020/02/11.
//

#ifndef AStarUtils_hpp
#define AStarUtils_hpp

#include "AStarNode.hpp"
#include "GameSpriteBase.hpp"

class AStarUtils
{
private:
    static AStarNode* findGoalNode(std::vector<AStarNode*>& openNodes,
                                   std::vector<AStarNode*>& closeNodes,
                                   AStarNode *currentNode,
                                   const Vec2& goalPos,
                                   GameSpriteBase *sprite);
    
public:
    static float calculateECost(const Vec2 &posA, const Vec2 &posB);
    static bool findNodeFromVector(std::vector<AStarNode*>& vector, AStarNode *node);
    static std::vector<Vec2> shortestRouteStack(GameSpriteBase *sprite, const Vec2 &startPos, const Vec2 &goalPos);
    
};

#endif /* AStarUtils_hpp */
