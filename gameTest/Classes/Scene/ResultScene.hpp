//
//  ResultScene.hpp
//  gameTest-mobile
//
//  リザルトシーン
//
//  Created by 丹野健介 on 2020/03/10.
//

#ifndef ResultScene_hpp
#define ResultScene_hpp

USING_NS_CC;

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ResultScene : public Layer
{
private:
    int m_clearTime; // クリアタイム
    int m_clearHp; // クリア時のHP
    int m_clearFoundCount; // クリア時の見つかった数
    int m_clearRank; // クリア時の総合評価
        
public:
    static Scene* createScene(int time, int hp, int foundCnt, int rank);
    static ResultScene* create(int time, int hp, int foundCnt, int rank);
    virtual bool init(int time, int hp, int foundCnt, int rank);
    
};

#endif /* ResultScene_hpp */
