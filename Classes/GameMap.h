//
//  GameMap.h
//  Zodiac
//
//  Created by AIRIA on 15-3-19.
//
//

#ifndef __Zodiac__GameMap__
#define __Zodiac__GameMap__

#include "CommonHeader.h"
#include "YZTile.h"

class GameMap:public Node
{
public:
    CREATE_FUNC(GameMap);
    virtual bool init();
    virtual void onEnter();
    
    void load(std::string mapName);
    
    void updateTilesPosition();
    
    /**
     * 使悬空的tile下落并且创建新的tile
     */
    void fallDownTileAndCreateForSubCol();
    
//##########################################################################################
    
    /**
     * 获取指定列的断层列
     * @param cols 存储断层的开始和结束行
     * @param row 从第几行开始检索
     * @param col 检索第几列
     */
    std::vector<SubCol> &getSubCols(std::vector<SubCol> &cols, int col);
    
    /**
     * 根据行列坐标获取一个tile元素
     */
    YZTile *getTileByCoordinate(int row,int col);
    
    /**
     * 获取指定列里面子列中空白的格子数量
     * @param sc 子列
     * @param col 母列
     * @param row 行
     */
    int getEmptyBlockNumFromSubCol(SubCol sc,int row,int col);
    
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
     * 获取指定tile的移动路线
     */
    void getRoutes(YZTile *tile);
    
    void swapTile(YZTile *t1, YZTile *t2);
    
    
    Vector<YZTile*> tiles;
    std::vector<int> virtualRows;
    
    // setter & getter
    CC_SYNTHESIZE(int, m_iRows, Rows);
    CC_SYNTHESIZE(int, m_iCols, Cols);
};

#endif /* defined(__Zodiac__GameMap__) */
