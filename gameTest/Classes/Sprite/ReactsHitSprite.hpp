//
//  ReactsHitSprite.hpp
//  gameTest-mobile
//
//  弾丸に当たった際に処理を行うスプライト
//
//  Created by 丹野健介 on 2020/04/20.
//

#ifndef ReactsHitSprite_hpp
#define ReactsHitSprite_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameSpriteBase.hpp"

class ReactsHitSprite : public GameSpriteBase
{
protected:
    /// 弾丸に当たった際に実施する処理
    std::function<void()> m_hitAction;
    
public:
    static ReactsHitSprite* create(const std::string& filename, const Vec2& pos, ::directcion direction, std::function<void()> hitAction);
    virtual bool initWithFileName(const std::string& filename, const Vec2 &pos, ::directcion direction, std::function<void()> hitAction);
    virtual void hitToBullet(int damage, ::directcion bulletDirection);
    
};


#endif /* ReactsHitSprite_hpp */
