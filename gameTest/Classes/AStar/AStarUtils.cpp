//
//  AStarUtils.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/02/11.
//

#include "AStarUtils.hpp"

/**
    2座標間の推定移動コストを計算する
 
    @param posA 座標A
    @param posB 座標B
    @return 座標Aと座標Bの推定最短移動コスト
 */
float AStarUtils::calculateECost(const Vec2 &posA, const Vec2 &posB)
{
    return fabsf(posA.x - posB.x) + fabsf(posA.y - posB.y);
}


/**
    ノードVectorの中に、引数で与えられたノードと同じ座標のものがあるかチェックする
 
    @param vector ノードの配列
    @param node 探すノード
    @return true：vectorに同じものがある / false：ない
 */
bool AStarUtils::findNodeFromVector(std::vector<AStarNode*>& vector, AStarNode *node)
{
    for (AStarNode* i : vector) {
        if (i->pos == node->pos) {
            return true;
        }
    }
    return false;
}


/**
    スタート座標からゴール座標までの最短経路を返す
 
    @param 移動するゲームスプライト
    @param startPos スタートのワールド座標
    @param goalPos ゴールのワールド座標
    @return スタートからゴールまでの最短経路
 */
std::vector<Vec2> AStarUtils::shortestRouteStack(GameSpriteBase *sprite,
                                                 const Vec2 &startPos,
                                                 const Vec2 &goalPos)
{
    std::vector<AStarNode*> openNodes;
    std::vector<AStarNode*> closeNodes;
    AStarNode *startNode = new AStarNode(startPos, goalPos, nullptr);
    openNodes.push_back(startNode);
    
    // スタート座標とゴール座標から、ゴールノードを求める
    AStarNode *goalNode = AStarUtils::findGoalNode(openNodes, closeNodes, startNode, goalPos, sprite);
    
    if (goalNode) {
        return goalNode->shortestRouteStack();
    }
    return std::vector<Vec2>();
}


/**
    A*アルゴリズムを使って、スタートノードから目的地までの経路探索を行う
 
    @param openNodes 検証予定のノード
    @param closeNodes 検証済のノード
    @param currentNode 検証中のノード
    @param goalPos 目的地のワールド座標
    @param 移動するゲームスプライト
    @return ゴールノード
 */
AStarNode* AStarUtils::findGoalNode(std::vector<AStarNode*>& openNodes,
                                    std::vector<AStarNode*>& closeNodes,
                                    AStarNode *currentNode,
                                    const Vec2& goalPos,
                                    GameSpriteBase *sprite)
{
    // 目的地についているかチェック
    if (currentNode->pos == goalPos) {
        return currentNode;
    }
    
    // 経路探索
    // 上
    AStarNode *upNode = new AStarNode(Vec2{ currentNode->pos.x, currentNode->pos.y - 1.0f }, goalPos, currentNode);
    if (sprite->canMovePos(upNode->pos) &&
        !AStarUtils::findNodeFromVector(openNodes, upNode) &&
        !AStarUtils::findNodeFromVector(closeNodes, upNode))
    {
        openNodes.push_back(upNode);
    }
    else {
        delete upNode;
    }
    
    // 右
    AStarNode *rightNode = new AStarNode(Vec2{ currentNode->pos.x + 1.0f, currentNode->pos.y }, goalPos, currentNode);
    if (sprite->canMovePos(rightNode->pos) &&
        !AStarUtils::findNodeFromVector(openNodes, rightNode) &&
        !AStarUtils::findNodeFromVector(closeNodes, rightNode))
    {
        openNodes.push_back(rightNode);
    }
    else {
        delete rightNode;
    }
    
    // 下
    AStarNode *downNode = new AStarNode(Vec2{ currentNode->pos.x, currentNode->pos.y + 1.0f }, goalPos, currentNode);
    if (sprite->canMovePos(downNode->pos) &&
        !AStarUtils::findNodeFromVector(openNodes, downNode) &&
        !AStarUtils::findNodeFromVector(closeNodes, downNode))
    {
        openNodes.push_back(downNode);
    }
    else {
        delete downNode;
    }
    
    // 左
    AStarNode *leftNode = new AStarNode(Vec2{ currentNode->pos.x - 1.0f, currentNode->pos.y }, goalPos, currentNode);
    if (sprite->canMovePos(leftNode->pos) &&
        !AStarUtils::findNodeFromVector(openNodes, leftNode) &&
        !AStarUtils::findNodeFromVector(closeNodes, leftNode))
    {
        openNodes.push_back(leftNode);
    }
    else {
        delete leftNode;
    }
    
    // 上下左右の検証が終わったら、現在検証中のノードを検証済みとする
    openNodes.erase(openNodes.begin());
    closeNodes.push_back(currentNode);
    
    // 最短経路推定値でソート(昇順)
    std::sort(openNodes.begin(), openNodes.end(), [](const AStarNode *nodeA, const AStarNode *nodeB) {
        return nodeA->aCost + nodeA->eCost < nodeB->aCost + nodeB->eCost;
    });
    
    // 近いところから再起で検証
    while (!openNodes.empty()) {
        return AStarUtils::findGoalNode(openNodes, closeNodes, openNodes.front(), goalPos, sprite);
    }
    
    // 見つからなかったらnullptrを返す(到達不可）
    return nullptr;
}
