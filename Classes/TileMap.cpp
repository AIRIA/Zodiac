//
//  TileMap.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#include "TileMap.h"


bool TileMap::init()
{
    return true;
}

//MARK:parent method

void TileMap::onEnter()
{
    Node::onEnter();
    auto width = YZ_TILE_SIZE * m_iCols;
    auto height = YZ_TILE_SIZE * m_iRows;
    setContentSize(Size(width,height));
    //初始化地图的背景图块儿
    for (auto tile : tiles) {
        auto type = tile->getTileType();
        if (type==1) {
            continue;
        }
        auto block = Sprite::create("Tile/block.png");
        block->setAnchorPoint(Point::ZERO);
        block->setPosition(Point(YZ_TILE_SIZE*tile->getCol(),YZ_TILE_SIZE*tile->getRow()));
        addChild(block);
        addChild(tile,1);
    }
    
    srand(time(nullptr));
    
    updateTilePositionByCol();
//    updateTilePostionByRow();
}

// MARK: 逻辑方法和游戏业务相关

void TileMap::load(std::string mapName)
{
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(mapName);
    
    rapidjson::Document doc;
    doc.Parse<0>(jsonStr.c_str());
    log("%s",jsonStr.c_str());
    
    rapidjson::Value &val = doc["tiles"];
    if (val.IsArray())
    {
        m_iRows = val.Size();
        int idx = 0;
        rapidjson::Value &element = val[idx];
        m_iCols= element.Size();
        
        log("row:%d,col:%d",m_iRows,m_iCols);
        
        /* 按照从下往上的顺序存储 第一行在最下面 */
        for (int i=m_iRows-1; i>-1; i--)
        {
            
            rapidjson::Value &rowVal = val[i];
            
            for (int j=0; j<m_iCols; j++)
            {
                
                
                auto tileType = atoi(rowVal[j].GetString());
                auto tile = YZTile::create();
                tile->setTileType((TileType)tileType);
                tile->setRow(m_iRows-1-i);
                tile->setCol(j);
                tiles.pushBack(tile);
            }
        }
    }
}




void TileMap::getNextRoutes(YZTile *tile,int row,int col)
{
    row = row==-1?tile->getRow():row;
    col = col==-1?tile->getCol():col;
    
    auto downTile = getTileByCoordinate(row-1, col);
    auto leftTile = getTileByCoordinate(row-1, col-1);
    auto rightTile = getTileByCoordinate(row-1, col+1);
    
    Route route = Route(row-1,-1);
    
    if (downTile && downTile->getTileType()==TileType::kYZ_EMPTY)
    {
        route.col = col;
    }
    else if(leftTile && leftTile->getTileType()==TileType::kYZ_EMPTY)
    {
        route.col = col-1;
    }
    else if(rightTile && rightTile->getTileType()==TileType::kYZ_EMPTY)
    {
        route.col = col+1;
    }
    
    if (route.col==-1)
    { //不能再向任何位置移动
        if (tile->routes.size()>0)
        {
            auto it = --(tile->routes.end());
            auto targetTile = getTileByCoordinate(it->row, it->col);
            targetTile->setPosition(tile->getPosition());
            swapTile(tile, targetTile);
        }
        return;
    }
    tile->routes.push_back(route);
    
    getNextRoutes(tile,route.row,route.col);
    
}

void TileMap::updateTilePositionByCol()
{
    for (auto col=0; col<m_iCols; col++)
    {
        for (auto row=1; row<m_iRows; row++)
        {
            auto tile = getTileByCoordinate(row, col);
            
            if (tile)
            {
                if (tile->getTileType()==kYZ_EMPTY) {

                }
                else if(tile->getTileType()==kYZ_EXIST)
                {
                    //move down
                    auto emptyNum = getEmptyNumUnderRow(row, col);
                    if(emptyNum==0)
                    {
                        continue;
                    }
                    auto targetTile = getTileByCoordinate(row-emptyNum, col);
                    auto targetTilePos = targetTile->getPosition();
                    targetTile->setPosition(tile->getPosition());
                    swapTile(targetTile, tile);
                    auto moveAct = MoveTo::create(YZ_MOVE_DOWN_DURATION*emptyNum, targetTilePos);
                    tile->runAction(Sequence::create(moveAct, nullptr));
                }
                
            }
        }
    }
    
    //开始检测每一列的最上方是否有空白的地方
    for(auto col=0;col<m_iCols;col++)
    {
        log("---------%d--------",col);
        printDataByCol(col);
        this->fillEmptyFromTop(col);
        

    }
    
    
}

void TileMap::updateTilePositionByRow()
{
    /**
     * 按行更新 从倒数第二行开始遍历 最后一行不可能会再下落
     * 先便利自己的下方是否有可以移动的 没有的话 再向斜下方寻找
     * 当找到自己的位置以后 立刻更新自己的坐标为目标位置的坐标
     * 全部的元素都找到自己的目标位置以后 开始执行动画 来移动到相应的位置
     */
    
    for (auto row=1; row<m_iRows; row++)
    {
        
        for (auto col=0; col<m_iCols; col++)
        {
            
            auto tile = getTileByCoordinate(row, col);
            if (tile && tile->getTileType()!=TileType::kYZ_EMPTY)
            {
                log("currow:%d,curcol:%d",tile->getRow(),tile->getCol());
                getNextRoutes(tile);
                tile->printRoutes();
                tile->updatePosition();
            }
            
        }
        
    }
    delayRun(YZ_DELAY_CHECK, [&]()->void{
        checkEmptyBlock();
    });
    
}

void TileMap::checkEmptyBlock()
{
    /**
     * 全局检测一遍以后要重复检测最上面的是否还有空置的图块儿
     *
     */
    
    bool flag = false; //标识位 表示是否检测到了空的 方法会递归调用来重复检测 直到没有空白元素存在的
    
    for (auto col=0; col<m_iCols; col++)
    {
        auto tile = getTileByCoordinate(m_iRows-1, col);
        if (tile && tile->getTileType()==TileType::kYZ_EMPTY)
        {
            tile->createRandomElement();
            getNextRoutes(tile);
            tile->updatePosition();
            flag = true;
        }
    }
    
    if(flag)
    {
        delayRun(YZ_DELAY_CHECK, [&]()->void{
            this->checkEmptyBlock();
        });
    }
    
}


void TileMap::fillEmptyBlockByCol(int col)
{
    
    auto emptyNum = 0;
    for (auto row=0; row<m_iRows; row++)
    {
        auto tile = getTileByCoordinate(row, col);
        if (tile)
        {
            if (tile->getTileType()==kYZ_EMPTY) {
                emptyNum++;
                if (row==m_iRows-1) {

                }
                
            }
            else if(tile->getTileType()==kYZ_EXIST)
            {
                //move down
                auto targetTile = getTileByCoordinate(row-emptyNum, col);
                auto targetTilePos = targetTile->getPosition();
                targetTile->setPosition(tile->getPosition());
                swapTile(targetTile, tile);
                auto moveAct = MoveTo::create(YZ_MOVE_DOWN_DURATION*emptyNum, targetTilePos);
                tile->runAction(Sequence::create(moveAct, nullptr));
            }
            
        }
    }
    
    
//    bool flag = false; //表示是否有列的顶端元素移动位置了
//    for (auto col=0; col<m_iCols; col++)
//    {
//        auto topTile = getTopTile(col);
//        getNextRoutes(topTile);
//        if(topTile->routes.size()>0)
//        {
//            flag = true;
//            topTile->updatePosition();
//        }
//    }
//    if (flag) {
//        delayRun(YZ_DELAY_CHECK, [this]()->void{
//            this->fillEmptyBlockByCol();
//        });
//    }
}

void TileMap::fillEmptyFromTop(int col)
{
    auto row = m_iRows - 1;
    auto tile = getTileByCoordinate(row, col);
    if (tile && tile->getTileType()==TileType::kYZ_EMPTY)
    {
        auto emptyNum = getEmptyNumByCol(col);
        if (emptyNum==0) {
            return;
        }

        auto targetTile = getTileByCoordinate(m_iRows-emptyNum, col);
        auto targetTilePos = targetTile->getPosition();
        targetTile->setPosition(tile->getPosition());
        tile->createRandomElement();
        swapTile(targetTile, tile);
        tile->setPosition(Point(YZ_TILE_SIZE*tile->getCol(),YZ_TILE_SIZE*(m_iRows)));
        auto moveAct = MoveTo::create(YZ_MOVE_DOWN_DURATION*emptyNum, Point(YZ_TILE_SIZE*tile->getCol(),YZ_TILE_SIZE*(m_iRows-emptyNum)));
        tile->runAction(Sequence::create(moveAct, nullptr));

        delayRun(YZ_DELAY_CHECK, [col,this]()->void{
            this->fillEmptyFromTop(col);
        });
    }
    log("changed over");
}



// MARK:辅助型的方法

void TileMap::swapTile(YZTile *t1, YZTile *t2)
{
    auto tempRow = t1->getRow();
    auto tempCol = t1->getCol();
    
    t1->setRow(t2->getRow());
    t1->setCol(t2->getCol());
    
    t2->setRow(tempRow);
    t2->setCol(tempCol);
    
    tiles.swap(t1, t2);
}

void TileMap::delayRun(float duration,const std::function<void()> &handler)
{
    auto calllater = CallFunc::create([handler]()->void{
        handler();
    });
    
    auto delay = DelayTime::create(duration);
    runAction(Sequence::create(delay,calllater, nullptr));
}

YZTile *TileMap::getTileByCoordinate(int row, int col)
{
    if (col==m_iCols || col==-1 || row==m_iRows || row==-1)
    {
        return nullptr;
    }
    
    auto idx = row*m_iCols+col;
    auto tile = tiles.at(idx);
    if (tile->getTileType()==TileType::kYZ_DISABLE)
    {
        return nullptr;
    }
    return tiles.at(idx);
}

YZTile *TileMap::getTopTile(int col)
{
    for (auto row=m_iRows-1; row>-1; row--)
    {
        //如果顶层是空的需要创建一个新的
        auto tile = getTileByCoordinate(row, col);
        if(row==(m_iRows-1) && tile && tile->getTileType()==TileType::kYZ_EMPTY)
        {
            tile->createRandomElement();
            return tile;
        }
        if (tile==nullptr || tile->getTileType()==TileType::kYZ_EMPTY)
        {
            continue;
        }
        return tile;
    }
    return nullptr;
}

int TileMap::getEmptyNumByCol(int col)
{
    auto emptyNum = 0;
    for (auto row=0; row<m_iRows; row++)
    {
        auto tile = getTileByCoordinate(row, col);
        if (tile)
        {
            if (tile->getTileType()==kYZ_EMPTY) {
                emptyNum++;
            }
        }
    }
    return emptyNum;
}

int TileMap::getEmptyNumUnderRow(int row, int col)
{
    auto emptyNum = 0;
    for (auto i=0; i<row; i++)
    {
        auto tile = getTileByCoordinate(i, col);
        if (tile && tile->getTileType()==TileType::kYZ_EMPTY)
        {
            emptyNum++;
        }
    }
    return emptyNum;
}

void TileMap::printDataByCol(int col)
{
    for (auto row=0; row<m_iRows; row++) {
        auto tile = getTileByCoordinate(row, col);
        if (tile) {
            log("row:%d,col:%d,type:%d",row,col,tile->getTileType());
        }

    }
}
