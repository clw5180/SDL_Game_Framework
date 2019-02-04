//
//  CPlayer.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 12/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__Player__
#define __SDL_Game_Programming_Book__Player__

#include <iostream>
#include <vector>
#include "sdlgameobject.h"
#include "gameobjectfactory.h"

class CPlayer : public CSDLGameObject
{
public:
    
    CPlayer();
    virtual ~CPlayer() {}
    
    virtual void load(std::unique_ptr<CLoaderParams> const &pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void collision();
    
    virtual std::string type() { return "CPlayer"; }
    
private:
    
    // bring the player back if there are lives left
    void ressurect();
    
    // handle any input from the keyboard, mouse, or joystick
    void handleInput();
    
    // handle any animation for the player
    void handleAnimation();
};

// for the factory
class CPlayerCreator : public CBaseCreator
{
    CGameObject* createGameObject() const
    {
        return new CPlayer();
    }
};


#endif /* defined(__SDL_Game_Programming_Book__Player__) */
