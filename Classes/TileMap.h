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
    
    void load(std::string mapName);
    Vector<YZTile*> tiles;
    
    CC_SYNTHESIZE(int, m_iRows, Rows);
    CC_SYNTHESIZE(int, m_iCols, Cols);
    
};

#endif /* defined(__Zodiac__TileMap__) */
