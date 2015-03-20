//
//  GameMap.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-19.
//
//

#include "GameMap.h"

bool GameMap::init()
{
    return true;
}

void GameMap::onEnter()
{
    Node::onEnter();
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
    
    for (auto col=0; col<m_iCols; col++)
    {
        virtualRows.push_back(0);
    }
    
    updateTilesPosition();
    
}

//MARK: PERFECT

void GameMap::load(std::string mapName)
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

void GameMap::updateTilesPosition()
{
    log("初始化状态");
    printData();
    fallDownTileAndCreateForSubCol();
}

void GameMap::fallDownTileAndCreateForSubCol()
{
    bool flag = true; //标识是否已经填充完了所有的列
    auto time = 0;
    while(flag || time<2)
    {
        flag = false;
        time++;
        //按照列的方式遍历 使得每一个断层的悬空tile都下落
        for (auto col=0; col<m_iCols; col++)
        {
            
            std::vector<SubCol> subColVec;
            getSubCols(subColVec, col);
            
            //遍历当前列的断层
            for (auto subCol : subColVec)
            {
                //针对一个断层自下而上检查是否有可以下落的  如果是顶层则创建新的 如果是断层顶部 则从旁边列 获取  循环检测 知道没有任何空白的
                for(auto row=subCol.began;row<subCol.end;row++)
                {
                    auto tile = getTileByCoordinate(row, col);
                    if (row==m_iRows-1)
                    { //顶层
                        if (tile->getTileType()==TileType::kYZ_EMPTY)
                        {
                            virtualRows[col] = virtualRows.at(col)+1;
                            tile->createRandomElement();
                            tile->setPosition(Point(YZ_TILE_SIZE*tile->getCol(),YZ_TILE_SIZE*(tile->getRow()+virtualRows[col])));
                            flag = true;
                        }
                    }
                    //第一次循环 只判断降落 不判断斜方向
                    else if(row==(subCol.end-1) && time!=1) //断层的顶部 从旁边列 获取新的tile并交换位置 同时放入到tile的routes中
                    {
                        YZTile *source = nullptr;
                        auto subTopTile = getTileByCoordinate(subCol.end-1, col);
                        log("col:%d,subTopTile row:%d,col:%d",col,subTopTile->getRow(),subTopTile->getCol());
                        
                        while (true)
                        {
                            if (subTopTile->getTileType()==TileType::kYZ_EXIST) { //如果顶层有 就不执行任何逻辑
                                break;
                            }
                            
                            auto leftCol = col-1;
                            auto rightCol = col+1;
                            
                            if (leftCol>-1) {
                                auto leftTile = getTileByCoordinate(subCol.end-1, leftCol);
                                auto aboveLeft = getTileByCoordinate(subCol.end, leftCol);
                                if ((leftTile==nullptr || leftTile->getTileType()!=TileType::kYZ_EMPTY) && aboveLeft && aboveLeft->getTileType()==TileType::kYZ_EXIST)
                                {
                                    source = aboveLeft;
                                }
                                if (aboveLeft) //如果上方有位置 则只从这个方向获取新的元素
                                {
                                    break;
                                }
                            }
                            
                            if (rightCol<m_iCols) {
                                auto rightTile = getTileByCoordinate(subCol.end-1, rightCol);
                                auto aboveRight = getTileByCoordinate(subCol.end, rightCol);
                                
                                if ( (rightTile==nullptr || rightTile->getTileType()!=TileType::kYZ_EMPTY) && aboveRight && aboveRight->getTileType()==TileType::kYZ_EXIST)
                                {
                                    source = aboveRight;
                                    break;
                                }
                            }
                            break;
                        }
                        if (source)
                        {
                            auto pos = source->getPositionByCoordinate();
                            source->routes.push_back(Route(subTopTile->getRow(),subTopTile->getCol()));
                            getRoutes(subTopTile);
                            subTopTile->setPosition(source->getPositionByCoordinate());
                            for (auto route : subTopTile->routes)
                            {
                                source->routes.push_back(route);
                            }
                            swapTile(subTopTile, source);
                            
                            if (source->getPosition()==pos) {
                                source->stopAllActions();
                                source->updatePosition();
                            }
                            subTopTile->routes.clear();
                            log("------------");
                            source->printRoutes();
                        }
                    }
                    
                    
                    if(tile->getTileType()==TileType::kYZ_EXIST)
                    {
                        auto emptyNum = getEmptyBlockNumFromSubCol(subCol, row, col);
                        if (emptyNum==0 && row!=(m_iRows-1)) { //没有空的 跳过
                            continue;
                        }
                        
                        auto targetTile = getTileByCoordinate(row-emptyNum, col);
                        auto targetPos = targetTile->getPositionByCoordinate();
                        int gap = (tile->getPosition().y - targetPos.y)/YZ_TILE_SIZE;
                        auto moveAct = MoveTo::create(YZ_MOVE_DOWN_DURATION*gap, targetPos);
                        auto moveCallback = CallFuncN::create([](Node *node)->void{
                            auto tile = static_cast<YZTile*>(node);
                            
                            tile->updatePosition();
                        });
                        tile->cleanup();
                        tile->actionVec.pushBack(moveAct);
                        tile->actionVec.pushBack(moveCallback);
                        tile->runAction(Sequence::create(moveAct,moveCallback, NULL));
                        swapTile(tile, targetTile);
                        
                    }
                }
            }
        }
        printData();
    }
    
}


//###################################################################################################

//MARK: PERFECT

std::vector<SubCol> &GameMap::getSubCols(std::vector<SubCol> &cols, int col )
{
    /**
     * 从第一个不是disabled的地方 开始 到第一个disable的地方结束 为一列
     */
    
    bool flag = true;
    
    auto row = 0;
    
    while (row<m_iRows) {
        auto began = row,end = 0;
        for (; row<m_iRows;row++)
        {
            auto tile = getTileByCoordinate(row, col);
            if (tile)
            {
                if (row==m_iRows-1)
                {
                    end = m_iRows;
                    row++; //break 也需要更改变量
                    break;
                }
                if (flag==false)
                {
                    continue;
                }
                else
                {
                    flag = false;
                }
                
                began = row;
                
            }
            else
            {
                end = row;
                row++;
                break;
            }
        }
        if (end>began)
        {
//            log("getSbuCol-- began:%d,end:%d,col:%d",began,end,col);
            cols.push_back(SubCol(began,end));
        }
    }
    
    return cols;
    
}

//MARK:PERFECT
YZTile *GameMap::getTileByCoordinate(int row, int col)
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

//MARK:PERFECT
int GameMap::getEmptyBlockNumFromSubCol(SubCol sc,int row, int col)
{
    auto emptyNum = 0;
    for (auto i=sc.began; i<row; i++)
    {
        auto tile = getTileByCoordinate(i, col);
        if (tile && tile->getTileType()==TileType::kYZ_EMPTY)
        {
            emptyNum++;
        }
    }
    return emptyNum;
}

void GameMap::printDataByCol(int col)
{
    for (auto row=0; row<m_iRows; row++) {
        auto tile = getTileByCoordinate(row, col);
        if (tile) {
            log("row:%d,col:%d,type:%d",row,col,tile->getTileType());
        }
        
    }
}

void GameMap::printDataByRow(int row)
{
    std::string data = "[";
    for (auto col=0; col<m_iCols; col++)
    {
        auto tile = getTileByCoordinate(row, col);
        if (tile==nullptr) {
            data = data+"\"1\"";
        }
        else
        {
            char tileType[5];
            sprintf(tileType, "%d",tile->getTileType());
            
            data = data+"\""+tileType+"\"";
        }
        if (col<m_iCols-1)
        {
            data += ", ";
        }
        
    }
    data += "]";
    log("%s",data.c_str());
}

void GameMap::printData()
{
    for (auto row=m_iRows-1; row>-1; row--)
    {
        printDataByRow(row);
    }
}

void GameMap::swapTile(YZTile *t1, YZTile *t2)
{
    auto tempRow = t1->getRow();
    auto tempCol = t1->getCol();
    
    t1->setRow(t2->getRow());
    t1->setCol(t2->getCol());
    
    t2->setRow(tempRow);
    t2->setCol(tempCol);
    
    tiles.swap(t1, t2);
}

void GameMap::getRoutes(YZTile *tile)
{
    /*
     * 寻找方向 下 左边 右边
     * 左边 和 右边的 不可以是一个subCol的顶端
     */
    
    auto row=tile->getRow(),col=tile->getCol();
    
    
    while (true) {
        
        YZTile *next=nullptr;
        auto leftCol = col - 1;
        auto rightCol = col + 1;
        auto downRow = row - 1;
        
        if (downRow>-1)
        {
            next = getTileByCoordinate(row-1, col);
        }
        
        if (leftCol>-1 && downRow>-1 && next && next->getTileType()==TileType::kYZ_EXIST)
        {
            next = getTileByCoordinate(row-1, col-1);
        }
        
        if (rightCol<m_iCols && downRow>-1 && next && next->getTileType()==TileType::kYZ_EXIST)
        {
            next = getTileByCoordinate(row-1, col+1);
        }
        
        if (next && getTileByCoordinate(next->getRow()+1, next->getCol()) && next->getTileType()==TileType::kYZ_EMPTY)
        {
            row = next->getRow();
            col = next->getCol();
            auto route = Route(row, col);
            tile->routes.push_back(route);
            continue;
        }
        break;
    }
    
    if (tile->routes.size() > 0)
    {
        auto it = --(tile->routes.end());
        auto targetTile = getTileByCoordinate(it->row, it->col);
        targetTile->setPosition(tile->getPositionByCoordinate());
        swapTile(tile, targetTile);
    }
    
}

