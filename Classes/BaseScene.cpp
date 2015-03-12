//
//  BaseScene.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#include "BaseScene.h"

void BaseScene::run()
{
    auto runningScene = Director::getInstance()->getRunningScene();
    auto nextScene = Scene::create();
    nextScene->addChild(this);
    if (runningScene==nullptr)
    {
        Director::getInstance()->runWithScene(nextScene);
        return;
    }
    Director::getInstance()->replaceScene(nextScene);
    
}

void BaseScene::loadFramesWithFile(std::string path)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);
}