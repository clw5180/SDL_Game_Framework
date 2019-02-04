//
//  gamestatemachine.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__GameStateMachine__
#define __SDL_Game_Programming_Book__GameStateMachine__

#include <vector>
#include "gamestate.h"

class CGameStateMachine
{
public:
    
    CGameStateMachine() {}
    ~CGameStateMachine() {}
    
    void update();
    void render();
    
    void pushState(CGameState* pState);
    void changeState(CGameState* pState);
    void popState();
    
    void clean();

	std::vector<CGameState*>& getGameStates() { return m_gameStates; }
    
private:
    std::vector<CGameState*> m_gameStates;
};

#endif /* defined(__SDL_Game_Programming_Book__GameStateMachine__) */
