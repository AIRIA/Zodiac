//
//  LevelMap.h
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#ifndef __Zodiac__LevelMap__
#define __Zodiac__LevelMap__

#include "CommonHeader.h"

/**
 * 关卡地图的滚动类
 * 玩家可以选择关卡
 */

class LevelMap:public TableViewDelegate,public TableViewDataSource,public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(LevelMap);
    
    virtual void scrollViewDidScroll(ScrollView* view) {};
    virtual void scrollViewDidZoom(ScrollView* view) {}
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual void onEnter();
    
};

#endif /* defined(__Zodiac__LevelMap__) */
