//
//  SceneManager.cpp
//  Doodler
//
//  Created by Kiko on 2016/05/05.
//
//

#include "SceneManager.hpp"
#include "DrawingCanvas.hpp"

using namespace cocos2d;

static SceneManager* sharedSceneManager = nullptr;

#pragma mark public method

SceneManager::SceneManager()
{
    this->drawingCanvas = nullptr;
    this->networkingWrapper = new NetworkingWrapper();
    this->networkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager()
{
    
}

SceneManager* SceneManager::getInstance()
{
    if (!sharedSceneManager)
    {
        sharedSceneManager = new SceneManager();
    }
    
    return sharedSceneManager;
}

void SceneManager::enterSoloGame()
{
    this->loadDrawingScene(false);
}

void SceneManager::returnToLobby()
{
    if(this->drawingCanvas)
    {
        Director::getInstance()->popScene();
        this->drawingCanvas = nullptr;
    }
}

void SceneManager::connectAndEnterNetworkedGame()
{
    this->networkingWrapper->attemptToJoinGame();
}

void SceneManager::sendData(const void *data, unsigned long length)
{
    this->networkingWrapper->sendData(data, length);
}

#pragma mark - private method

void SceneManager::loadDrawingScene(bool networked)
{
    auto scene = Scene::create();
    
    this->drawingCanvas = DrawingCanvas::create();
    this->drawingCanvas->setNetworkedSession(networked);
    
    scene->addChild(drawingCanvas);
    
    Director::getInstance()->pushScene(scene);
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state) {
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
            
        case ConnectionState::CONNECTING:
            CCLOG("Connecting");
            break;
        case ConnectionState::CONNECTED:
            CCLOG("Connected!");
            if(!this->drawingCanvas)
            {
                this->loadDrawingScene(true);
            }
            break;
    }
}

void SceneManager::receivedData(const void *data, unsigned long length)
{
    if (this->drawingCanvas)
    {
        this->drawingCanvas->receivedData(data, length);
    }
}