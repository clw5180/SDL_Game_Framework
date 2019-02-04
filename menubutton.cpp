//
//  MenuObject.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 10/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "menubutton.h"
#include "inputhandler.h"

CMenuButton::CMenuButton() : CSDLGameObject(), m_callback(0), m_bReleased(true)
{
}

void CMenuButton::load(std::unique_ptr<CLoaderParams> const &pParams)
{
    CSDLGameObject::load(std::move(pParams));
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void CMenuButton::draw()
{
	CSDLGameObject::draw();
}

void CMenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
    
    if(pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
       && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
    {
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            
            if(m_callback != 0)
            {
                m_callback();
            }
            
            m_bReleased = false;
        }
        else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void CMenuButton::clean()
{
	CSDLGameObject::clean();
}
