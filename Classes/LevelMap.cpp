//
//  LevelMap.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#include "LevelMap.h"
#include "YZTableView.h"

enum NodeTag{
    kYZMapView
};

bool LevelMap::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto mapView = YZTableView::create(this, Director::getInstance()->getWinSize());
    mapView->setDirection(ScrollView::Direction::VERTICAL);
    mapView->setPosition(Point::ZERO);
    mapView->setDelegate(this);
    mapView->setBounceable(true);
    mapView->reloadData();
    mapView->setTag(kYZMapView);
    addChild(mapView);
    
    return true;
}


void LevelMap::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    
}

Size LevelMap::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto size = Director::getInstance()->getWinSize();
    return Size(size.width,size.width/768.0f*1024.0f);
}

TableViewCell* LevelMap::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    log("idx:%ld",idx);
    if (!cell) {
        cell = new TableViewCell();
        cell->autorelease();
    }
    char fileName[50];
    sprintf(fileName, "map_%02ld.png",idx+1);
    Sprite *sprite = nullptr;
    if (idx>11) {
        sprintf(fileName, "Map/map_%02ld.png",idx+1);
        sprite = Sprite::create(fileName);
    }
    else
    {
        sprite = Sprite::createWithSpriteFrameName(fileName);
    }
    
    sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    auto size = Director::getInstance()->getWinSize();
    sprite->setScale(size.width/768.0f);
    cell->addChild(sprite);
    
    return cell;
}

ssize_t LevelMap::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 15;
}

void LevelMap::onEnter()
{
    Layer::onEnter();
    auto table = static_cast<YZTableView*>(getChildByTag(kYZMapView));
    table->setContentOffset(Point(0,0));
    auto container = table->getContainer();
    log("container:width=%f,height=%f",container->getContentSize().width,container->getContentSize().height);

}



