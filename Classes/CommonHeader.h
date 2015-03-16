//
//  framework.h
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#ifndef Zodiac_framework_h
#define Zodiac_framework_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "VisibleRect.h"
#include "tinyxml2/tinyxml2.h"
#include <vector>

using namespace cocos2d;
using namespace cocos2d::extension;

using namespace std;

//Mark:defines

#define YZ_DESIGN_WIDTH 640
#define YZ_DESIGN_HEIGHT 960
#define YZ_SPRITE_NAME(url) Sprite::createWithSpriteFrameName(url)
#define YZ_TILE_SIZE 80

#endif
