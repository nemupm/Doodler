//
//  SceneManager.hpp
//  Doodler
//
//  Created by Kiko on 2016/05/05.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "NetworkingWrapper.h"
class DrawingCanvas;

class SceneManager : public NetworkingDelegate {
    
public:
    SceneManager();
    ~SceneManager();
    
    static SceneManager* getInstance();
    void enterSoloGame();
    void returnToLobby();
    void connectAndEnterNetworkedGame();

private:
    DrawingCanvas* drawingCanvas;
    NetworkingWrapper* networkingWrapper;
    
    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
    void loadDrawingScene(bool networked);
};


#endif /* SceneManager_hpp */
