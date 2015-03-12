//
//  HomeScene.h
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#ifndef __Zodiac__HomeScene__
#define __Zodiac__HomeScene__

#include "BaseScene.h"

class HomeScene:public BaseScene
{
public:
    CREATE_FUNC(HomeScene);
    virtual bool init();
    virtual void onEnter();
};


#endif /* defined(__Zodiac__HomeScene__) */
