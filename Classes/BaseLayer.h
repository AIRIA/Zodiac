//
//  BaseLayer.h
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#ifndef __Zodiac__BaseLayer__
#define __Zodiac__BaseLayer__

#include "CommonHeader.h"

/**
 * BaseLayer 是用来适配手机屏幕的层
 * 竖屏游戏 分为上中下 横屏游戏 分为左中右
 * 层分为三个结构 上 中 下 三部分
 *
 */

class BaseLayer:public Layer
{
public:
    BaseLayer():m_fScaleFactor(0.0f),m_pTop(nullptr),m_pMid(nullptr),m_pBtm(nullptr){};
    CREATE_FUNC(BaseLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
protected:
    Size m_winSize;
    Size m_frameSize;
    float m_fScaleFactor;
    Layer *m_pTop,*m_pMid,*m_pBtm;
    
private:
    Layer *createLayer(Point anchorPos,Point pos);

};

#endif /* defined(__Zodiac__BaseLayer__) */
