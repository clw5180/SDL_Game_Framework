//
//  gameobjectfactory.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 24/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_GameObjectFactory_h
#define SDL_Game_Programming_Book_GameObjectFactory_h

#include <string>
#include <map>
#include <iostream>
#include "gameobject.h"

class CBaseCreator
{
public:
    
    virtual CGameObject* createGameObject() const = 0;
    virtual ~CBaseCreator() {}
};

class GameObjectFactory
{
public:
    
    static GameObjectFactory* Instance()
    {
        if(pInstance == 0)
        {
            pInstance = new GameObjectFactory();
        }
        
        return pInstance;
    }
    
    bool registerType(std::string typeID, CBaseCreator* pCreator)
    {
        std::map<std::string, CBaseCreator*>::iterator it = m_creators.find(typeID);
        
        // if the type is already registered, do nothing
        if(it != m_creators.end())
        {
            delete pCreator;
        }
        
        m_creators[typeID] = pCreator;
        
        return true;
    }
    
    CGameObject* create(std::string typeID)
    {
        std::map<std::string, CBaseCreator*>::iterator it = m_creators.find(typeID);
        
        if(it == m_creators.end())
        {
            std::cout << "could not find type: " << typeID << "\n";
            return NULL;
        }
    
        CBaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }
    
private:
    
    GameObjectFactory() {}
    ~GameObjectFactory() {}
    
    std::map<std::string, CBaseCreator*> m_creators;
    
    static GameObjectFactory* pInstance;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif
