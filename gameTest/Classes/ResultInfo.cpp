//
//  ResultInfo.cpp
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/19.
//

#include "ResultInfo.hpp"

#pragma mark -
#pragma mark Init
/**
    ResultInfoのcreateメソッド
    
    @param stageNum ステージ番号
    @return ResultInfo
 */
ResultInfo* ResultInfo::create(const int stageNum)
{
    ResultInfo *ref = new (std::nothrow) ResultInfo();
    if (ref && ref->init(stageNum))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}


/**
    初期化処理
    
    @param stageNum ステージ番号
    @return ResultInfo
 */
bool ResultInfo::init(const int stageNum)
{
    this->m_stageNum = stageNum;
    return true;
}


#pragma mark -
#pragma mark Getter
/**
    総合スコアのゲッター
 
    @param スコア合計
 */
int ResultInfo::totalScore()
{
    return this->m_timeScore + this->m_hpScore + this->m_foundScore;
}
