//
//  Lobby.cpp
//  Doodler
//
//  Created by Noriyuki Matsuoka on 2016/04/28.
//
//

#include "Lobby.hpp"
#include "DrawingCanvas.hpp"
#include "Constants.h"

using namespace cocos2d;

bool Lobby::init()
{
    if(!Node::init())
    {
        return false;
    }

    LayerColor* background = LayerColor::create(Color4B(COLOR_WHITE));
    this->addChild(background);
    return true;
}

void Lobby::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* logo = Sprite::create("doodlerLogo.png");
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    logo->setPosition(Vec2(0.5f*visibleSize.width, 0.75f*visibleSize.height));
    CCLOG("lobby-width:%f", visibleSize.width);
    CCLOG("lobby-height:%f", visibleSize.height);
    this->addChild(logo);
    
    // soloButton
    ui::Button* soloButton = ui::Button::create();
    soloButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    soloButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height * 0.4f));
    soloButton->loadTextures("soloButton.png", "soloButtonPressed.png");
    soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    this->addChild(soloButton);
    // duoButton
    ui::Button* duoButton = ui::Button::create();
    duoButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    duoButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.25f));
    duoButton->loadTextures("duoButton.png", "duoButtonPressed.png");
    duoButton->addTouchEventListener(CC_CALLBACK_2(Lobby::duoPressed, this));
    this->addChild(duoButton);
}

void Lobby::onEnter()
{
    Node::onEnter();
    this->setupUI();
}

void Lobby::soloPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        Scene* scene = Scene::create();
        
        DrawingCanvas* drawingCanvas = DrawingCanvas::create();
        scene->addChild(drawingCanvas);
        
        Director::getInstance()->pushScene(scene);
    }
}

void Lobby::duoPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
}
