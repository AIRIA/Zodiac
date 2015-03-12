//
//  YZTableView.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-9.
//
//

#include "YZTableView.h"

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f
#define BOUNCE_BACK_FACTOR   0.35f

YZTableView* YZTableView::create()
{
    return YZTableView::create(nullptr, Size::ZERO);
}

void YZTableView::setContentOffset(cocos2d::Vec2 offset, bool animated)
{
//    log("%f %f,offset %f",maxContainerOffset().y,minContainerOffset().y,offset.y);

    offset.y = offset.y<minContainerOffset().y?minContainerOffset().y:offset.y;
    offset.y = offset.y>maxContainerOffset().y?maxContainerOffset().y:offset.y;
    
    if (animated)
    { //animate scrolling
        this->setContentOffsetInDuration(offset, BOUNCE_DURATION);
    }
    else
    { //set the container position directly
        if (!_bounceable)
        {
            const Vec2 minOffset = this->minContainerOffset();
            const Vec2 maxOffset = this->maxContainerOffset();
            
            offset.x = MAX(minOffset.x, MIN(maxOffset.x, offset.x));
            offset.y = MAX(minOffset.y, MIN(maxOffset.y, offset.y));
        }
        
        _container->setPosition(offset);
        
        if (_delegate != nullptr)
        {
            _delegate->scrollViewDidScroll(this);
        }
    }

}

YZTableView* YZTableView::create(TableViewDataSource* dataSource, Size size)
{
    return YZTableView::create(dataSource, size, nullptr);
}

YZTableView* YZTableView::create(TableViewDataSource* dataSource, Size size, Node *container)
{
    YZTableView *table = new (std::nothrow) YZTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();
    
    return table;
}

