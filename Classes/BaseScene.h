//
//  BaseScene.h
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#ifndef __Zodiac__BaseScene__
#define __Zodiac__BaseScene__

#include "BaseLayer.h"

class BaseScene:public BaseLayer
{
public:
    CREATE_FUNC(BaseScene);
    virtual void run();
    virtual void loadFramesWithFile(std::string path);
};

#endif /* defined(__Zodiac__BaseScene__) */
