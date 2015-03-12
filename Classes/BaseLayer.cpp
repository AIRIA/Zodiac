//
//  BaseLayer.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#include "BaseLayer.h"

bool BaseLayer::init()
{
    auto res = true;
    if (!Layer::init()) {
        res = false;
    }
    
    m_winSize = Director::getInstance()->getWinSize();
    m_frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    m_fScaleFactor = m_frameSize.width/YZ_DESIGN_WIDTH;
    
    return res;
}

Layer *BaseLayer::createLayer(Point anchorPos,Point pos)
{
    auto part = Layer::create();
    part->setContentSize(Size(YZ_DESIGN_WIDTH,YZ_DESIGN_HEIGHT));
    part->ignoreAnchorPointForPosition(false);
    part->setScale(m_fScaleFactor);
    part->setAnchorPoint(anchorPos);
    part->setPosition(pos);
    addChild(part);
    return part;
}

void BaseLayer::onEnter()
{
    Layer::onEnter();
    m_pBtm = createLayer(Point::ANCHOR_BOTTOM_LEFT, VisibleRect::leftBottom());
    m_pMid = createLayer(Point::ANCHOR_MIDDLE, VisibleRect::center());
    m_pTop = createLayer(Point::ANCHOR_TOP_LEFT, VisibleRect::leftTop());
}

void BaseLayer::onExit()
{
    Layer::onExit();
}