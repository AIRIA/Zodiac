//
//  HomeScene.cpp
//  Zodiac
//
//  Created by AIRIA on 15-3-5.
//
//

#include "HomeScene.h"
#include "BaseSprite.h"
#include "ElasticButton.h"
#include "MainScene.h"
#include "GameScene.h"

bool HomeScene::init()
{
    auto res = true;
    if (!BaseScene::init()) {
        res = false;
    }
    
    return res;
}

void HomeScene::onEnter()
{
    BaseScene::onEnter();
    
    auto loadingBg = Sprite::create("Map/loading.png");
    loadingBg->setScale(YZ_DESIGN_WIDTH/loadingBg->getContentSize().width);
    loadingBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    m_pBtm->addChild(loadingBg);
    
    auto logo = Sprite::create("Map/logo_cn.png");
    logo->setPosition(Point(YZ_DESIGN_WIDTH/2,900));
    m_pBtm->addChild(logo);
    
    auto start = ElasticButton::create("Button/blue_big_btn.png","");
    start->setPosition(Point(YZ_DESIGN_WIDTH/2,300));
    start->setTouchHandler([]()->void{
//        MainScene::create()->run();
        GameScene::create()->run();
    });
    m_pBtm->addChild(start);
    
    

}

