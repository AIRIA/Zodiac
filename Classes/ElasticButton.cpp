//
//  ElasticButton.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#include "ElasticButton.h"

ElasticButton *ElasticButton::create(std::string path, std::string label)
{
    auto button = new ElasticButton();
    if (button && button->initWithFile(path)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

ElasticButton *ElasticButton::createWithSpriteFrameName(std::string fileName, std::string label)
{
    auto button = new ElasticButton();
    if (button && button->initWithSpriteFrameName(fileName)) {
        button->autorelease();
        return  button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

void ElasticButton::setTouchHandler(std::function<void ()> handler)
{
    onTouchHandler = handler;
}

void ElasticButton::onEnter()
{
    BaseSprite::onEnter();
    __initEventListeners();
    setTouchBeganHandler([](BaseSprite *bs)->void{
        auto scaleAction = ScaleTo::create(0.5f, 0.8f);
        auto scaleEase = EaseElasticOut::create(scaleAction);
        bs->runAction(scaleEase);
    });
    
    setTouchMovedHandler([](BaseSprite *bs)->void{
        auto scaleAction = ScaleTo::create(0.5f, 1.0f);
        auto scaleEase = EaseElasticOut::create(scaleAction);
        auto scaleCallback = CallFunc::create([bs]()->void{
            
        });
        bs->runAction(Sequence::create(scaleEase,scaleCallback, nullptr));
    });
    
    setTouchEndedHandler([&](BaseSprite *bs)->void{
        bs->getEventListener()->setEnabled(false);
        auto scaleAction = ScaleTo::create(0.5f, 1.0f);
        auto scaleEase = EaseElasticOut::create(scaleAction);
        
        auto scaleCallback = CallFunc::create([&,bs]()->void{
            bs->getEventListener()->setEnabled(true);
            if (this->onTouchHandler) {
                this->onTouchHandler();
            }
        });
        bs->runAction(Sequence::create(scaleEase,scaleCallback, nullptr));
    });
}
