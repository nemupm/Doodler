//
//  DrawingCanvas.hpp
//  Doodler
//
//  Created by Noriyuki Matsuoka on 2016/04/28.
//
//

#ifndef DrawingCanvas_hpp
#define DrawingCanvas_hpp

#include "cocos2d.h"
#include "CocosGUI.h"

class DrawingCanvas : public cocos2d::Node
{
public:
    CREATE_FUNC(DrawingCanvas);
    bool getNetworkedSession();
    void setNetworkedSession(bool networked);
    
protected:
    cocos2d::LayerColor* background;
    cocos2d::DrawNode* drawNode;
    cocos2d::Sprite* check;
    cocos2d::Color4F selectedColor;
    bool networkedSession;
    
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
    void setupMenus();
    void clearPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void backPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void colorChangedPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
};

#endif /* DrawingCanvas_hpp */
