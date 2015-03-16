//
//  Tile.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-12.
//
//

#include "YZTile.h"

bool YZTile::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void YZTile::printRoutes()
{
    auto routeLen = routes.size();
    
    for (auto idx = 0; idx<routeLen; idx++) {
        log("route----row:%d,col%d",routes.at(idx).row,routes.at(idx).col);
    }
}

void YZTile::updatePosition()
{
    if (routes.size()==0) {
        return;
    }
    auto curRoute = routes.at(0);
    auto nextPos = Point(YZ_TILE_SIZE*curRoute.col,YZ_TILE_SIZE*curRoute.row);
    auto move = MoveTo::create(YZ_MOVE_DOWN_DURATION, nextPos);
    auto callback1 = CallFunc::create([&]()->void{
        this->routes.erase(this->routes.begin());
        this->updatePosition();
    });
    
    runAction(Sequence::create(move,callback1, nullptr));

}

void YZTile::createRandomElement()
{
    removeAllChildren();
    auto randomItemIdx = rand()%6+1;
    char name[50];
    sprintf(name, "Tile/item_%d.png",randomItemIdx);
    auto ele = Sprite::create(name);
    ele->setAnchorPoint(Point::ZERO);
    addChild(ele);
    
    setTileType(TileType::kYZ_EXIST);
}

void YZTile::onEnter()
{
    Node::onEnter();
    auto isShow = rand()%10;
    setPosition(Point(YZ_TILE_SIZE*getCol(),YZ_TILE_SIZE*getRow()));
    if (isShow >5) {
        return;
    }
    createRandomElement();
    
    
}