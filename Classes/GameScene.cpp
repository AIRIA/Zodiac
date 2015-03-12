//
//  GameScene.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#include "GameScene.h"
#include "TileMap.h"

bool GameScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    loadMap();
    return true;
}

void GameScene::onEnter()
{
    BaseScene::onEnter();
    
    auto bg = Sprite::create("Map/BG_01.png");
    bg->setAnchorPoint(Point::ZERO);
    bg->setScale(m_winSize.width/bg->getContentSize().width);
    addChild(bg,-1);
    
    auto tileMap = TileMap::create();
    tileMap->load("Level/map.json");
    tileMap->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tileMap->setPosition(Point(YZ_DESIGN_WIDTH/2,YZ_DESIGN_HEIGHT/2));
    m_pMid->addChild(tileMap);
}

void GameScene::loadMap()
{
    
    
}