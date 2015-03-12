//
//  GameScene.h
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#ifndef __Zodiac__GameScene__
#define __Zodiac__GameScene__

#include "BaseScene.h"

class GameScene:public BaseScene
{
public:
    CREATE_FUNC(GameScene);
    virtual bool init();
    virtual void onEnter();
protected:
    void loadMap();
};

#endif /* defined(__Zodiac__GameScene__) */
