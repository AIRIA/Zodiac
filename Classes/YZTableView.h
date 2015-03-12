//
//  YZTableView.h
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#ifndef __Zodiac__YZTableView__
#define __Zodiac__YZTableView__

#include "CommonHeader.h"

class YZTableView:public TableView
{
public:
    static YZTableView* create();
    static YZTableView* create(TableViewDataSource* dataSource, Size size);
    static YZTableView* create(TableViewDataSource* dataSource, Size size, Node *container);
    virtual void setContentOffset(Vec2 offset, bool animated = false );
};

#endif /* defined(__Zodiac__YZTableView__) */