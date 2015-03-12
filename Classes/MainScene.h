//
//  MainScene.h
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#ifndef __Zodiac__MainScene__
#define __Zodiac__MainScene__

#include "BaseScene.h"

class MainScene:public BaseScene
{
public:
    CREATE_FUNC(MainScene);
    virtual bool init();
    virtual void onEnter();
};


#endif /* defined(__Zodiac__MainScene__) */
