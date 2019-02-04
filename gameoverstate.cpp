//
//  CGameOverState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 17/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "gameoverstate.h"
#include "mainmenustate.h"
#include "playstate.h"
#include "texturemanager.h"
//#include "AnimatedGraphic.h"
#include "game.h"
#include "menubutton.h"
#include "inputhandler.h"
#include "stateparser.h"

const std::string CGameOverState::s_gameOverID = "GAMEOVER";

void CGameOverState::s_gameOverToMain()
{
    CGame::Instance()->GetStateMachine()->changeState(new CMainMenuState());
}

void CGameOverState::s_restartPlay()
{
    CGame::Instance()->GetStateMachine()->changeState(new CPlayState());
}

void CGameOverState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}

void CGameOverState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool CGameOverState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    
    std::cout << "entering CGameOverState\n";
    return true;
}

bool CGameOverState::onExit()
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
    
    std::cout << m_gameObjects.size();
    
    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    TheInputHandler::Instance()->reset();
    
    std::cout << "exiting CGameOverState\n";
    return true;
}

void CGameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
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

