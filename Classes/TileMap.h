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
     * 更新一列中的子列
     * @param col 指定的列
     */
    void updateSubCols();
    
    /**
     * 获取指定列里面子列中空白的格子数量
     * @param sc 子列 
     * @param col 母列
     * @param row 行
     */
    int getEmptyBlockNumFromSubCol(SubCol sc,int row,int col);
    
    /**
     * 填充指定列中子列的空白位置 如果子列的顶部 无法获取新的元素 需要向斜上方查找
     * @return 如果存在空白列 返回true 
     */
    bool fillEmptyBlockForSubCol(SubCol sc,int col);
    
    /**
     * 让指定的tile下降到最底部 知道没有空白位置
     */
    void slideDownTargetTile(SubCol subCol,YZTile *tile);
    
    /**
     * 检测是否有空白的位置存在
     */
    void detectEmptyBlock();
    
    void createNewBlockBySubCol(SubCol subCol,int col,int virtualRow);
    
    /**
     * 查找每一咧不连续的空白处 并且是他们变成连续的
     */
    void findEmptyBlockForSubColAndReorder(SubCol sc,int col);
    
    /**
     * 按照列的方式检索是否有可以填充的新的tile的位置
     * 一列可能会被分割成了多个小的断层 需要分开判断
     */
    void updateTilePositionByCol();
    
    /**
     * 打印指定列的类型数据
     * @param col 要打印的列
     */
    void printDataByCol(int col);
    
    /**
     * 打印指定行的类型数据
     * @param row 要打印的行
     */
    void printDataByRow(int row);
    
    /**
     * 打印当前的阵型数据
     */
    void printData();
    
    
    /**
     * 获取指定列顶端的元素
     */
    YZTile *getTopTile(int col);
    
    
//    /* 初始化地图阵型的背景 */
//    void initMapBlock();
    
    Vector<YZTile*> tiles;
    
    std::vector<int> virtualRows;
    
    // setter & getter
    CC_SYNTHESIZE(int, m_iRows, Rows);
    CC_SYNTHESIZE(int, m_iCols, Cols);
    
    
    
    
    
};

#endif /* defined(__Zodiac__TileMap__) */
