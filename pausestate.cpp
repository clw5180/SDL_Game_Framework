//
//  CPauseState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 16/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "pausestate.h"
#include "mainmenustate.h"
#include "playstate.h"
//#include "texturemanager.h"
#include "game.h"
#include "menubutton.h"
#include "inputhandler.h"
#include "stateparser.h"

const std::string CPauseState::s_pauseID = "PAUSE";

void CPauseState::s_pauseToMain()
{
    CGame::Instance()->GetStateMachine()->changeState(new CMainMenuState());
}

void CPauseState::s_resumePlay()
{
    CGame::Instance()->GetStateMachine()->popState();
}

void CPauseState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}

void CPauseState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool CPauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    
    std::cout << "entering CPauseState\n";
    return true;
}

bool CPauseState::onExit()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
            delete m_gameObjects[i];
        }
        m_gameObjects.clear();
    }
    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    TheInputHandler::Instance()->reset();
    
    std::cout << "exiting CPauseState\n";
    return true;
}

void CPauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

