//
//  GameScene.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#include "GameScene.h"
#include "TileMap.h"
#include "GameMap.h"
#include "ElasticButton.h"

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
    
    auto tileMap = GameMap::create();
    tileMap->load("Level/map4.json");
    tileMap->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tileMap->setPosition(Point(YZ_DESIGN_WIDTH/2,YZ_DESIGN_HEIGHT/2));
    m_pMid->addChild(tileMap);
    
    auto btn = ElasticButton::create("Button/green_middle_btn.png", "");
    btn->setPosition(YZ_DESIGN_WIDTH/2,60);
    btn->setTouchHandler([tileMap]()->void{
//        tileMap->updateTilePositionByCol();
//        tileMap->fillEmptyBlockByCol() ;
//        tileMap->updateTilePositionByRow();
        GameScene::create()->run();
//        tileMap->updateTilesPosition();
//        tileMap->updateSubColsForCol(1);
//        tileMap->updateSubCols();
    });
//    tileMap->setScale(0.5f);
    m_pTop->addChild(btn);
}

void GameScene::loadMap()
{
    
    
}