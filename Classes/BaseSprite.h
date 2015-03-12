//
//  BaseSprite.h
//  Zodiac
//
//  Created by AIRIA on 15-3-6.
//
//

#ifndef __Zodiac__BaseSprite__
#define __Zodiac__BaseSprite__

#include "CommonHeader.h"

class BaseSprite:public Sprite
{
public:
    static BaseSprite *create(std::string path);
    static BaseSprite *createWithSpriteFrameName(std::string fileName);
    void setTouchBeganHandler(std::function<void(BaseSprite*)> handler);
    void setTouchMovedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchEndedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchMovedOutHandler(std::function<void(BaseSprite*)> handler);
    
    virtual void onEnter();

    EventListenerTouchOneByOne *getEventListener();
    
protected:
    std::function<void(BaseSprite*)> touchBeganHandler;
    std::function<void(BaseSprite*)> touchMovedHandler;
    std::function<void(BaseSprite*)> touchEndedHandler;
    std::function<void(BaseSprite*)> touchMovedOutHandler;
    
    void __initEventListeners();
    bool __isContainTouch(Touch *touch);
    EventListenerTouchOneByOne *m_pEventListener;

private:
    bool m_isMoveOut = false;
};

#endif /* defined(__Zodiac__BaseSprite__) */
