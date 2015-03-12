//
//  BaseSprite.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-6.
//
//

#include "BaseSprite.h"

BaseSprite *BaseSprite::create(std::string path)
{
    auto sprite = new BaseSprite();
    if (sprite && sprite->initWithFile(path))
    {
        sprite->autorelease();
        sprite->__initEventListeners();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

BaseSprite* BaseSprite::createWithSpriteFrameName(std::string fileName)
{
    auto sprite = new BaseSprite();
    if (sprite && sprite->initWithSpriteFrameName(fileName))
    {
        sprite->autorelease();
        sprite->__initEventListeners();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool BaseSprite::__isContainTouch(cocos2d::Touch *touch)
{
    auto location = this->convertToNodeSpace(touch->getLocation());
    auto size = getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(location)) {
        return true;
    }
    return false;
}

EventListenerTouchOneByOne *BaseSprite::getEventListener()
{
    return m_pEventListener;
}

void BaseSprite::__initEventListeners()
{
    m_pEventListener = EventListenerTouchOneByOne::create();
    m_pEventListener->setSwallowTouches(false);
    m_pEventListener->onTouchBegan = [](Touch *touch,Event *event)->bool{
        auto target = event->getCurrentTarget();
        auto bs = static_cast<BaseSprite*>(target);
        
        if (bs->__isContainTouch(touch))
        {
            if (bs->touchBeganHandler!=nullptr)
            {
                bs->touchBeganHandler(bs);
            }
            return true;
        }
        
        return false;
    };
    
    m_pEventListener->onTouchMoved = [&](Touch *touch,Event *event)->void{
        if (this->touchMovedHandler) {
            this->touchMovedHandler(this);
        }
        
        if (this->m_isMoveOut==false && this->__isContainTouch(touch) == false && this->touchMovedOutHandler)
        {
            this->touchMovedOutHandler(this);
            this->m_isMoveOut = true;
        }
        
    };
    
    m_pEventListener->onTouchEnded = [&](Touch *touch,Event *event)->void{
        if (this->touchEndedHandler) {
            this->touchEndedHandler(this);
        }
        this->m_isMoveOut = false;
    };

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pEventListener, this);
}

void BaseSprite::setTouchBeganHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchBeganHandler = handler;
}

void BaseSprite::setTouchMovedHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchMovedHandler = handler;
}

void BaseSprite::setTouchEndedHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchEndedHandler = handler;
}

void BaseSprite::setTouchMovedOutHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchMovedOutHandler = handler;
}

void BaseSprite::onEnter()
{
    Sprite::onEnter();
}
