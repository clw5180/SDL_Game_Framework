//
//  CPlayer.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 12/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "player.h"
#include "game.h"
#include "inputhandler.h"
//#include "TileLayer.h"
//#include "BulletHandler.h"
//#include "SoundManager.h"

using namespace std;

CPlayer::CPlayer()
{
}

void CPlayer::collision()
{
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet

	//clw note：意思应该是，如果不是无敌的，而且不是过关的情况，碰撞就会爆炸
    /*if(!m_invulnerable && !CGame::Instance()->getLevelComplete())
    {
        m_textureID = "largeexplosion";
        m_currentFrame = 0;
        m_numFrames = 9;
        m_width = 60;
        m_height = 60;
        m_bDying = true;
    }*/
}

void CPlayer::load(std::unique_ptr<CLoaderParams> const &pParams)
{
    // inherited load function
	CSDLGameObject::load(std::move(pParams));
    
    // can set up the players inherited values here
}

void CPlayer::draw()
{
    // player has no special drawing requirements
	CSDLGameObject::draw();
}

void CPlayer::handleAnimation()
{
    // if the player is invulnerable we can flash its alpha to let people know
    //if(m_invulnerable)
    //{
    //    // invulnerability is finished, set values back
    //    if(m_invulnerableCounter == m_invulnerableTime)
    //    {
    //        m_invulnerable = false;
    //        m_invulnerableCounter = 0;
    //        m_alpha = 255;
    //    }
    //    else // otherwise, flash the alpha on and off
    //    {
    //        if(m_alpha == 255)
    //        {
    //            m_alpha = 0;
    //        }
    //        else
    //        {
    //            m_alpha = 255;
    //        }
    //    }
    //    
    //    // increment our counter
    //    m_invulnerableCounter++;
    //}
    
    // if the player is not dead then we can change the angle with the velocity to give the impression of a moving helicopter
    if(!m_bDead)
    {
        if(m_velocity.getX() < 0)
        {
            m_angle = -10.0;
        }
        else if(m_velocity.getX() > 0)
        {
            m_angle = 10.0;
        }
        else
        {
            m_angle = 0.0;
        }
    }
    
    // our standard animation code - for helicopter propellors
    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void CPlayer::update()
{
    //if(CGame::Instance()->getLevelComplete())
    //{
    //    if(m_position.getX() >= CGame::Instance()->GetWindowWidth())
    //    {
    //        CGame::Instance()->setCurrentLevel(CGame::Instance()->getCurrentLevel() + 1);
    //    }
    //    else
    //    {
    //        m_velocity.setY(0);
    //        m_velocity.setX(3);
    //        CGameObject::update();
    //        handleAnimation();
    //    }
    //}
    //else
    //{
    //    // if the player is not doing its death animation then update it normally
    //    if(!m_bDying)
    //    {
    //        // reset velocity
    //        m_velocity.setX(0);
    //        m_velocity.setY(0);
    //        
    //        // get input
    //        handleInput();
    //        
    //        // do normal position += velocity update
    //        CGameObject::update();
    //        
    //        // update the animation
    //        handleAnimation();
    //    }
    //    else // if the player is doing the death animation
    //    {
    //        m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
    //        
    //        // if the death animation has completed
    //        if(m_dyingCounter == m_dyingTime)
    //        {
    //            // ressurect the player
    //            ressurect();
    //        }
    //        m_dyingCounter++;
    //    }
    //}
}

void CPlayer::ressurect()
{
	/*  CGame::Instance()->setPlayerLives(CGame::Instance()->getPlayerLives() - 1);

	  m_position.setX(10);
	  m_position.setY(200);
	  m_bDying = false;

	  m_textureID = "player";

	  m_currentFrame = 0;
	  m_numFrames = 5;
	  m_width = 101;
	  m_height = 46;*/
    
	//m_dyingCounter = 0;
	//m_invulnerable = true;
}

void CPlayer::clean()
{
    CSDLGameObject::clean();
}

void CPlayer::handleInput()
{
    if(!m_bDead)
    {
        // handle keys
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
        {
            m_velocity.setY(-m_moveSpeed);
        }
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < CGame::Instance()->GetWindowHeight() - 10)
        {
            m_velocity.setY(m_moveSpeed);
        }
        
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
        {
            m_velocity.setX(-m_moveSpeed);
        }
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < CGame::Instance()->GetWindowWidth())
        {
            m_velocity.setX(m_moveSpeed);
        }
        


        // */
        
        //// handle joysticks /      
        //if(TheInputHandler::Instance()->joysticksInitialised())    //clw 处理手柄
        //{
        //    if(TheInputHandler::Instance()->getButtonState(0, 2))
        //    {
        //        if(m_bulletCounter == m_bulletFiringSpeed)
        //        {
        //            TheSoundManager::Instance()->playSound("shoot", 0);
        //            TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
        //            m_bulletCounter = 0;
        //        }
        //        
        //        m_bulletCounter++;
        //    }
        //    else
        //    {
        //        m_bulletCounter = m_bulletFiringSpeed;
        //    }
        //    
        //    if((TheInputHandler::Instance()->getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < CGame::Instance()->GetWindowWidth()) || (TheInputHandler::Instance()->getAxisX(0, 1) < 0 && m_position.getX() > 0))
        //    {
        //        m_velocity.setX(m_moveSpeed * TheInputHandler::Instance()->getAxisX(0, 1));
        //    }
        //    
        //    if((TheInputHandler::Instance()->getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < CGame::Instance()->GetWindowHeight() - 10 ) || (TheInputHandler::Instance()->getAxisY(0, 1) < 0 && m_position.getY() > 0))
        //    {
        //        m_velocity.setY(m_moveSpeed * TheInputHandler::Instance()->getAxisY(0, 1));
        //    }
        //}
        //
        
    }
}