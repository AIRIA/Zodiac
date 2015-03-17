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
     * 按照列的方式检测每一列的顶层是否可以往下落 
     */
    void fillEmptyBlockByCol(int col);
    
    /**
     * 从指定列的顶部去填充下面空白的位置
     */
    void fillEmptyFromTop(int col);
    
    /**
     * 获取指定列的空白位置
     */
    int getEmptyNumByCol(int col);
    
    /**
     * 获取指定坐标下方的空白位置
     */
    int getEmptyNumUnderRow(int row,int col);
    
    /**
     * 延迟执行
     */
    void delayRun(float duration,const std::function<void()> &handler);
    
    /**
     * 按照行的方式检索是否有可以填充新tile的位置
     */
    void updateTilePositionByRow();
    
    /**
     * 获取指定列的断层列 
     * @param cols 存储断层的开始和结束行 
     * @param row 从第几行开始检索
     * @param col 检索第几列
     */
    std::vector<SubCol> &getSubCols(std::vector<SubCol> &cols,int row, int col);
    
    
    /**
     * 按照列的方式检索是否有可以填充的新的tile的位置
     * 一列可能会被分割成了多个小的断层 需要分开判断
     */
    void updateTilePositionByCol();
    
    /**
     * 打印指定列的类型数据
     */
    void printDataByCol(int col);
    
    
    /**
     * 获取指定列顶端的元素
     */
    YZTile *getTopTile(int col);
    
    
//    /* 初始化地图阵型的背景 */
//    void initMapBlock();
    
    Vector<YZTile*> tiles;
    
    // setter & getter
    CC_SYNTHESIZE(int, m_iRows, Rows);
    CC_SYNTHESIZE(int, m_iCols, Cols);
    
    
    
    
    
};

#endif /* defined(__Zodiac__TileMap__) */
