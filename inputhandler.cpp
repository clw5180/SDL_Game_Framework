//
//  CInputHandler.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 24/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "inputhandler.h"
#include "game.h"
#include <iostream>

CInputHandler* CInputHandler::s_pInstance = 0;

CInputHandler::CInputHandler() :  m_keystates(0),
m_bJoysticksInitialised(false),
m_mousePosition(new Vector2D(0,0))
{
    // create button states for the mouse
    for(int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
}

CInputHandler::~CInputHandler()
{
    // delete anything we created dynamically
    delete m_keystates;
    delete m_mousePosition;
    
    // clear our arrays
    m_joystickValues.clear();
    m_joysticks.clear();
    m_buttonStates.clear();
    m_mouseButtonStates.clear();
}

void CInputHandler::clean()
{
    // we need to clean up after ourselves and close the joysticks we opened
    if(m_bJoysticksInitialised)
    {
        for(unsigned int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void CInputHandler::initialiseJoysticks()
{
    // if we haven't already initialised the joystick subystem, we will do it here
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    // get the number of joysticks, skip init if there aren't any
    if(SDL_NumJoysticks() > 0)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            // create a new joystick
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            // if the joystick opened correctly we need to populate our arrays
            if(SDL_JoystickOpen(i))
            {
                // push back into the array to be closed later
                m_joysticks.push_back(joy);
                
                // create a pair of values for the axes, a vector for each stick
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0),new Vector2D(0,0)));
                
                // create an array to hold the button values
                std::vector<bool> tempButtons;
                
                // fill the array with a false value for each button
                for(int j = 0; j <  SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                // push the button array into the button state array
                m_buttonStates.push_back(tempButtons);
            }
            else
            {
                // if there was an error initialising a joystick we want to know about it
                std::cout << SDL_GetError();
            }
        }
        
        // enable joystick events
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        
        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)";
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
}

void CInputHandler::reset()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[RIGHT] = false;
    m_mouseButtonStates[MIDDLE] = false;
}

bool CInputHandler::isKeyDown(SDL_Scancode key) const
{
    if(m_keystates != 0)
    {
        if(m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    return false;
}

int CInputHandler::getAxisX(int joy, int stick) const
{
    if(m_joystickValues.size() > 0)
    {
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getX();
        }
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int CInputHandler::getAxisY(int joy, int stick) const
{
    if(m_joystickValues.size() > 0)
    {
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getY();
        }
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool CInputHandler::getButtonState(int joy, int buttonNumber) const
{
    return m_buttonStates[joy][buttonNumber];
}

bool CInputHandler::getMouseButtonState(int buttonNumber) const
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D* CInputHandler::getMousePosition() const
{
    return m_mousePosition;
}

void CInputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
				CGame::GetInstance()->Quit();
                break;
                
            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(event);
                break;
                
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(event);
                break;
                
            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(event);
                break;
                
            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
                
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
                
            case SDL_KEYDOWN:
                onKeyDown();
                break;
                
            case SDL_KEYUP:
                onKeyUp();
                break;
                
            default:
                break;
        }
    }
}

void CInputHandler::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}

void CInputHandler::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}

void CInputHandler::onMouseMove(SDL_Event &event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void CInputHandler::onMouseButtonDown(SDL_Event &event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void CInputHandler::onMouseButtonUp(SDL_Event &event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }
    
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void CInputHandler::onJoystickAxisMove(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    
	//clw note   �ҵı�ͨ�ֱ����尴�����úͷɻ���ս��example���Լ�sdlpal����һ��
	//event.jaxis.axis == 0��1��2��3���������Ұ���
    //event.jaxis.axis == 4���������°���
	//���������0��3�������ң�1��4��������


    // left stick move left or right        
    if(event.jaxis.axis == 0)      //clw �ҵı�ͨ�ֱ������Ӳ�һ����event.jaxis.axis == 1ʵ�ʿ������Ұ���
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}
    
    //left stick move up or down   
	//if (event.jaxis.axis == 1)
	if (event.jaxis.axis == 4)    //clw modify
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}
    
	/**********************clw���Դ���**********************************/
	/*         �������ԣ���ͨBTP-1126���ֱ���������Ϊ5                  */
	/*     ����0,1,2,3��ʾx���ƶ�������Debugģʽ�°����ֱ�ʮ�ּ��ġ����� */
	/*move_axis0~3����ֵΪ32767�������������ƶ�����move_axis4ֵΪ-256  */
	/*�����ֱ�ʮ�ּ��ġ���ʱ��move_axis0~3ֵΪ-256,��move_axis4ֵΪ32767*/
	/*˵����ͨBTP-1126���ֱ�x����axis0~3���ɱ�ʾ��y����axis4��ʾ��������*/
	/*SDL�ٷ���wiki����SDL_JoystickGetAxis�������������һ��Remarks��  */
	/*���ڶ����ִ���ҡ�ˣ�x��ͨ����axis 0��ʾ��y��ͨ����axis 1��ʾ      */
	
	int AvailableAxesNum = SDL_JoystickNumAxes(m_joysticks.back());

	Sint16 move_axis0;
	Sint16 move_axis1;
	Sint16 move_axis2;
	Sint16 move_axis3;
	Sint16 move_axis4;
	
	move_axis0 = SDL_JoystickGetAxis(m_joysticks.back(), 0);
	move_axis1 = SDL_JoystickGetAxis(m_joysticks.back(), 1);
	move_axis2 = SDL_JoystickGetAxis(m_joysticks.back(), 2);
	move_axis3 = SDL_JoystickGetAxis(m_joysticks.back(), 3);
	move_axis4 = SDL_JoystickGetAxis(m_joysticks.back(), 4);
	/*********************************************************************/

    // right stick move left or right  
    //if(event.jaxis.axis == 3)
    //{
    //    if (event.jaxis.value > m_joystickDeadZone)
    //    {
    //        m_joystickValues[whichOne].second->setX(1);
    //    }
    //    else if(event.jaxis.value < -m_joystickDeadZone)
    //    {
    //        m_joystickValues[whichOne].second->setX(-1);
    //    }
    //    else
    //    {
    //        m_joystickValues[whichOne].second->setX(0);
    //    }
    //}
    
    // right stick move up or down
    //if(event.jaxis.axis == 4)
    //{
		//if (event.jaxis.value > m_joystickDeadZone)
		//{
		//	m_joystickValues[whichOne].second->setY(1);
		//}
		//else if (event.jaxis.value < -m_joystickDeadZone)
		//{
		//	m_joystickValues[whichOne].second->setY(-1);
		//}
		//else
		//{
		//	m_joystickValues[whichOne].second->setY(0);
		//}
    //}
}

void CInputHandler::onJoystickButtonDown(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    
    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void CInputHandler::onJoystickButtonUp(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    
    m_buttonStates[whichOne][event.jbutton.button] = false;
}