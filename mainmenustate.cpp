//
//  CMenuState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//
#include <iostream>
#include "mainmenustate.h"
//#include "texturemanager.h"
#include "game.h"
#include "menubutton.h"
#include "playstate.h"
#include "inputhandler.h"
#include "stateparser.h"
//#include <assert.h>

const std::string CMainMenuState::s_menuID = "MENU";

// Callbacks
void CMainMenuState::s_menuToPlay()
{
    CGame::Instance()->GetStateMachine()->changeState(new CPlayState());
}

void CMainMenuState::s_exitFromMenu()
{
    CGame::Instance()->quit();
}

// end callbacks

void CMainMenuState::update()
{
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_menuToPlay();
	}
    if(!m_gameObjects.empty())
    {
			for(int i = 0; i < m_gameObjects.size(); i++)
			{
				if(m_gameObjects[i] != 0)
				{
					m_gameObjects[i]->update();
				}
			}
    }
}

void CMainMenuState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool CMainMenuState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    std::cout << "entering CMenuState\n";
    return true;
}

bool CMainMenuState::onExit()
{
    m_exiting = true;
    
    // clean the game objects
    if(m_loadingComplete && !m_gameObjects.empty())
    {
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
    }

	m_gameObjects.clear();

    
    /* clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
	*/
    
    // reset the input handler
    TheInputHandler::Instance()->reset();
    
    std::cout << "exiting CMenuState\n";
    return true;
}

void CMainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            // if they are of type CMenuButton then assign a callback based on the id passed in from the file
            if(dynamic_cast<CMenuButton*>(m_gameObjects[i]))
            {
                CMenuButton* pButton = dynamic_cast<CMenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}

