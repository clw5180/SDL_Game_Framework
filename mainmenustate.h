//
//  menustate.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __MAINMENUSTATE__
#define __MAINMENUSTATE__

#include <vector>
#include "menustate.h"
#include "gameobject.h"

class CMainMenuState : public CMenuState
{
public:
    
    virtual ~CMainMenuState() {}

    virtual void update();
    virtual void render();
    
    virtual bool onEnter(); 
    virtual bool onExit(); 
    
    virtual std::string getStateID() const { return s_menuID; }
    
private:
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    // call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    std::vector<CGameObject*> m_gameObjects;
};

#endif /* defined(__SDL_Game_Programming_Book__MenuState__) */
