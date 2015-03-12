//
//  ElasticButton.h
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#ifndef __Zodiac__ElasticButton__
#define __Zodiac__ElasticButton__

#include "BaseSprite.h"

/**
 * 像果冻一样的按钮 有弹性可伸缩
 */

class ElasticButton:public BaseSprite
{
public:
    static ElasticButton *create(std::string path,std::string label);
    static ElasticButton *createWithSpriteFrameName(std::string fileName,std::string label);
    
    void setTouchHandler(std::function<void()>) ;
    

    virtual void onEnter();
    
protected:
    /**
     * 触摸后的回调函数
     */
    std::function<void()> onTouchHandler;
};

#endif /* defined(__Zodiac__ElasticButton__) */
