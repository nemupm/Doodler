//
//  DrawingCanvas.cpp
//  Doodler
//
//  Created by Noriyuki Matsuoka on 2016/04/28.
//
//

#include "DrawingCanvas.hpp"
#include "Constants.h"

using namespace cocos2d;
bool DrawingCanvas::init()
{
    if(!Node::init())
    {
        return false;
    }
    background = LayerColor::create(Color4B(COLOR_WHITE));
    this->addChild(this->background);
    this->drawNode = DrawNode::create();
    this->addChild(this->drawNode);
    
    this->selectedColor = COLOR_GREEN;
    return true;
}

void DrawingCanvas::onEnter()
{
    Node::onEnter();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setContentSize(visibleSize);
    this->drawNode->setContentSize(visibleSize);
    
    this->setupTouchHandling();
    this->setupMenus();
}

void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
    static float lastRadius = INITIAL_RADIUS;

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        lastRadius = INITIAL_RADIUS;

        return true;
    };
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        
        float distance = lastTouchPos.distance(touchPos);
        
        float dt = 1.0f / 60.0f;
        float rc = 1.0f;
        float alpha = dt / (rc + dt);
        float radius = (alpha * distance) + (1.0f - alpha) * lastRadius;
        
        drawNode->drawSegment(lastTouchPos, touchPos, radius, this->selectedColor);
        
        lastRadius = radius;
        lastTouchPos = touchPos;
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void DrawingCanvas::setupMenus()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    ui::Button* clearButton = ui::Button::create();
    clearButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    clearButton->setPosition(Vec2(visibleSize.width, visibleSize.height));
    clearButton->loadTextures("clearButton.png", "clearButtonPressed.png");
    clearButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::clearPressed, this));
    this->addChild(clearButton);
    
    ui::Button* backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::backPressed, this));
    this->addChild(backButton);
    
    this->check = Sprite::create("checkMark.png");
    this->check->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->check->setNormalizedPosition(Vec2(0.5f, 0.5f));
    
    Node* colorButtonLayout = Node::create();
    colorButtonLayout->setContentSize(Size(visibleSize.width, visibleSize.height * 0.2f));
    colorButtonLayout->setAnchorPoint(Vec2(0.5f, 0.0f));
    colorButtonLayout->setPosition(Vec2(visibleSize.width * 0.5f, 0.0f));
    this->addChild(colorButtonLayout);
    
    for (int i = 1; i <= 5; ++i)
    {
        cocos2d::Color4F colorOrder[5] = {
            COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE
        };
        ui::Button* colorButton = ui::Button::create();
        colorButton->setAnchorPoint(Vec2(0.5f, 0.0f));
        colorButton->setPosition(Vec2(visibleSize.width * i * (1.0f/6.0f), 0.0f));
        colorButton->loadTextures("colorSwatch.png", "colorSwatch.png");
        colorButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangedPressed, this));
        colorButton->setColor(Color3B(colorOrder[i - 1]));
        colorButtonLayout->addChild(colorButton);
        
        if (i == 3) {
            colorButton->addChild(check);
        }
    }
}

void DrawingCanvas::clearPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        drawNode->clear();
    }
}

void DrawingCanvas::backPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}

void DrawingCanvas::colorChangedPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    ui::Button* pressedButton = static_cast<ui::Button*>(pSender);
    pressedButton->cocos2d::Node::setScale(0.85f);
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        this->check->retain();
        this->check->removeFromParent();
        pressedButton->addChild(this->check);
        this->check->release();
        this->selectedColor = static_cast<Color4F>(pressedButton->getColor());
        pressedButton->cocos2d::Node::setScale(1.0f);
    }
    else if (eEventType == ui::Widget::TouchEventType::CANCELED)
    {
        pressedButton->cocos2d::Node::setScale(1.0f);
    }
}

bool DrawingCanvas::getNetworkedSession()
{
    return this->networkedSession;
}

void DrawingCanvas::setNetworkedSession(bool networked)
{
    this->networkedSession = networked;
}