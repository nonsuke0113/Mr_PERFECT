//
//  ResultInfo.hpp
//  gameTest-mobile
//
//  リザルト情報
//
//  Created by 丹野健介 on 2020/04/19.
//

#ifndef ResultInfo_hpp
#define ResultInfo_hpp

USING_NS_CC;

#include "cocos2d.h"
#include <vector>

class ResultInfo : public Ref
{
protected:
    
public:
    /// ステージ番号
    int m_stageNum;
    /// クリア時間
    int m_clearTime;
    /// クリア時のHP
    int m_clearHp;
    /// 敵に見つかった回数
    int m_clearFoundCount;
    /// タイムスコア
    int m_timeScore;
    /// HPスコア
    int m_hpScore;
    /// 発見数スコア
    int m_foundScore;
    
    static ResultInfo* create(const int stageNum);
    virtual bool init(const int stageNum);
    int totalScore();
};

#endif /* ResultInfo_hpp */
