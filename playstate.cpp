//
//  CPlayState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include <iostream>
#include "playstate.h"
#include "gameoverstate.h"
#include "pausestate.h"
#include "game.h"
#include "inputhandler.h"
//#include "LevelParser.h"
//#include "Level.h"
//#include "BulletHandler.h"

const std::string CPlayState::s_playID = "PLAY";

void CPlayState::update()
{
    if(m_loadingComplete && !m_exiting)
    {
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            CGame::Instance()->GetStateMachine()->pushState(new CPauseState());
        }
         
   
        
		//if (CGame::Instance()->getPlayerLives() == 0)
		//{
		//	CGame::Instance()->GetStateMachine()->changeState(new CGameOverState());
		//}
        
      /*  if(pLevel != 0)
        {
            pLevel->update();
        }*/
    }
}

void CPlayState::render()
{
    if(m_loadingComplete)
    {
        //if(pLevel != 0)
        //{
        //    pLevel->render();
        //}
		std::cout << "clw: CPlayState::render" << std::endl;
        
    }
}

bool CPlayState::onEnter()
{
    //CGame::Instance()->setPlayerLives(1);  //clw note:ÉèÖÃÉúÃüÖµ
    
    //LevelParser levelParser;
    //pLevel = levelParser.parseLevel(CGame::Instance()->getLevelFiles()[CGame::Instance()->getCurrentLevel() - 1].c_str());
    
    //TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", CGame::Instance()->GetRenderer());
    //TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", CGame::Instance()->GetRenderer());
    //TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", CGame::Instance()->GetRenderer());
    //TheTextureManager::Instance()->load("assets/lives.png", "lives", CGame::Instance()->GetRenderer());
    
    if(pLevel != 0)
    {
        m_loadingComplete = true;
    }
    
    std::cout << "entering CPlayState\n";
    return true;
}

bool CPlayState::onExit()
{
    m_exiting = true;
    
    TheInputHandler::Instance()->reset();
    
    std::cout << "exiting CPlayState\n";
    return true;
}
