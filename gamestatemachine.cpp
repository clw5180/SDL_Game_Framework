//
//  CGameStateMachine.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "gamestatemachine.h"
#include <iostream>

void CGameStateMachine::clean()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();

        delete m_gameStates.back();
        
        m_gameStates.clear();
    }
}

void CGameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
	}
}

void CGameStateMachine::render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}

void CGameStateMachine::pushState(CGameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void CGameStateMachine::popState()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }
    
    m_gameStates.back()->resume();
}

void CGameStateMachine::changeState(CGameState *pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return; // do nothing
        }

		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
    }

	// initialise it
    pState->onEnter();
    
    // push back our new state
    m_gameStates.push_back(pState);
}