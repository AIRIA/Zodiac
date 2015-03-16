//
//  TileMap.h
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#ifndef __Zodiac__TileMap__
#define __Zodiac__TileMap__

#include "CommonHeader.h"
#include "YZTile.h"

class TileMap:public Node
{
public:
    CREATE_FUNC(TileMap);
    virtual bool init();
    virtual void onEnter();
    
    /** 
     * 加载地图配置文件 
     */
    void load(std::string mapName);
    
    /**
     * 交换两个tile的位置
     */
    void swapTile(YZTile *t1,YZTile *t2);
    
    /** 
     *获取一个tile到达指定位置经过的所有点 
     */
    void getNextRoutes(YZTile *tile,int row=-1,int col=-1);

    /**
     * 根据行列坐标获取一个tile元素
     */
    YZTile *getTileByCoordinate(int row,int col);
    
    /**
     * 重复检测是否有空闲的图块儿存在 如果存在的话 需要创建新的随机元素来填补空白的位置 直到全部填满
     */
    void checkEmptyBlock();
    
    /**
     * 延迟执行
     */
    void delayRun(float duration,const std::function<void()> &handler);
    
//    /* 初始化地图阵型的背景 */
//    void initMapBlock();
    
    Vector<YZTile*> tiles;
    
    CC_SYNTHESIZE(int, m_iRows, Rows);
    CC_SYNTHESIZE(int, m_iCols, Cols);
    
    
    
    void updateTilePostion();
    
};

#endif /* defined(__Zodiac__TileMap__) */
