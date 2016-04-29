//
//  Lobby.hpp
//  Doodler
//
//  Created by Noriyuki Matsuoka on 2016/04/28.
//
//

#ifndef Lobby_hpp
#define Lobby_hpp

#include "CocosGUI.h"

class Lobby : public cocos2d::Node{
public:
    CREATE_FUNC(Lobby);
protected:
    bool init() override;
    void onEnter() override;
    void setupUI();
    void soloPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void duoPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
};

#endif /* Lobby_hpp */
