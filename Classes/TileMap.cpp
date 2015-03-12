//
//  TileMap.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#include "TileMap.h"

#define YZ_TILE_SIZE 80


bool TileMap::init()
{
    return true;
}

void TileMap::onEnter()
{
    Node::onEnter();
    auto width = YZ_TILE_SIZE * m_iCols;
    auto height = YZ_TILE_SIZE * m_iRows;
    setContentSize(Size(width,height));
    
    for (auto tile : tiles) {
        auto type = tile->getTileType();
        if (type==1) {
            continue;
        }
        auto block = Sprite::create("Tile/block.png");
        block->setAnchorPoint(Point::ZERO);
        tile->addChild(block);
        tile->setPosition(Point(YZ_TILE_SIZE*tile->getCol(),YZ_TILE_SIZE*tile->getRow()));
        addChild(tile);
    }
    
    

}

void TileMap::load(std::string mapName)
{
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile("Level/map.json");
    
    rapidjson::Document doc;
    doc.Parse<0>(jsonStr.c_str());
    log("%s",jsonStr.c_str());
    
    rapidjson::Value &val = doc["tiles"];
    if (val.IsArray()) {
        m_iRows = val.Size();
        int idx = 0;
        rapidjson::Value &element = val[idx];
        m_iCols= element.Size();
        
        log("row:%d,col:%d",m_iRows,m_iCols);
        
        /* 按照从下往上的顺序存储 第一行在最下面 */
        for (int i=m_iRows-1; i>-1; i--) {
            
            rapidjson::Value &rowVal = val[i];
            
            for (int j=m_iCols-1; j>-1; j--) {
                
                
                auto tileType = atoi(rowVal[j].GetString());
                auto tile = YZTile::create();
                tile->setTileType(tileType);
                tile->setRow(m_iRows-1-i);
                tile->setCol(j);
                tiles.pushBack(tile);
            }
        }
        
//        log("tile num:%ld",tiles.size());
        
//        auto tileIt = tiles.begin();
//        while (tileIt!=tiles.end()) {
//            
//            log("tileType:%d",(*tileIt)->getTileType());
//            
//            tileIt++;
//        }
        
//        log("%d",tiles[7][1]);
        
    }
}

