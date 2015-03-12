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


class YZTile:public Node
{
public:
    CREATE_FUNC(YZTile);
    virtual bool init();
    
    /**
     * tile的类型 普通元素 阻挡元素 空 etc
     */
    CC_SYNTHESIZE(int, tileType, TileType);
    CC_SYNTHESIZE(int, m_iRow, Row);
    CC_SYNTHESIZE(int, m_iCol, Col);
};


#endif /* defined(__Zodiac__Tile__) */
