//
//  MainScene.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#include "MainScene.h"
#include "LevelMap.h"

bool MainScene::init()
{
    if (!BaseScene::init()) {
        return false;
    }
    loadFramesWithFile("Map/MapFrame1.plist");
    loadFramesWithFile("Map/MapFrame2.plist");
    loadFramesWithFile("Map/MapFrame3.plist");
    
    
    return true;
}

void MainScene::onEnter()
{
    BaseScene::onEnter();
    auto levelMap = LevelMap::create();
//    levelMap->setScale(YZ_DESIGN_WIDTH/768.0f);
    log("%f   %f",levelMap->getContentSize().width,levelMap->getContentSize().height);
    addChild(levelMap);
}