//
//  Tile.h
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#ifndef __Zodiac__Tile__
#define __Zodiac__Tile__

#include "CommonHeader.h"

enum TileType{
    kYZ_EMPTY=0,  // 可以放置元素
    kYZ_DISABLE=1, // 无法放置元素
    kYZ_EXIST=2
};

#define YZ_DELAY_CHECK 1.2f
#define YZ_MOVE_DOWN_DURATION 1.2f

class Route
{
public:
    Route();
    Route(int r,int c):row(r),col(c){};
    int row,col;
};

class SubCol
{
public:
    SubCol(int b,int e):began(b),end(e){};
    int began,end;
};

class YZTile:public Node
{
public:
    CREATE_FUNC(YZTile);
    virtual bool init();

    /**
     * 存放他可以到达的指定位置途中经过的所有位置
     */
    std::vector<Route> routes;
    /**
     * 打印可以行走的路线
     */
    void printRoutes();
    /**
     * 按照路线更新自己的位置
     */
    void updatePosition();
    /**
     * 生成随机的消除元素
     */
    void createRandomElement();
    
    virtual void onEnter();
    
    /**
     * tile的类型 普通元素 阻挡元素 空 etc
     */
    CC_SYNTHESIZE(TileType, tileType, TileType);
    CC_SYNTHESIZE(int, m_iRow, Row);
    CC_SYNTHESIZE(int, m_iCol, Col);
    
};


#endif /* defined(__Zodiac__Tile__) */
