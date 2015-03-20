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
    m_iVirtualRow = 0;
    actionSeqVec.push_back(ActionSeq());
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

void YZTile::runActionSeqVec()
{
    Vector<FiniteTimeAction*> actionVec;
    for (auto actionSeq : actionSeqVec)
    {
        Vector<FiniteTimeAction*> subActionVec;
        for (auto route:actionSeq.routes)
        {
            auto moveTo = MoveTo::create(YZ_MOVE_DOWN_DURATION, Point(YZ_TILE_SIZE*route.col,YZ_TILE_SIZE*route.row));
            subActionVec.pushBack(moveTo);
        }
        if (actionSeq.fallAction)
        {
            subActionVec.pushBack(actionSeq.fallAction);
        }
        actionVec.pushBack(subActionVec);
    }
    if (actionVec.size()) {
        auto callback = CallFuncN::create([](Node *node)->void{
            auto self = static_cast<YZTile*>(node);
            self->actionSeqVec.clear();
            self->actionSeqVec.push_back(ActionSeq());
        });
        actionVec.pushBack(callback);
        runAction(Sequence::create(actionVec));
    }
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

Point YZTile::getPositionByCoordinate()
{
    return Point(YZ_TILE_SIZE*getCol(),YZ_TILE_SIZE*getRow());
}

void YZTile::onEnter()
{
    Node::onEnter();
    auto isShow = rand()%10;
    setPosition(getPositionByCoordinate());
    if (isShow >4) {
        return;
    }
//    createRandomElement();
    
    
}