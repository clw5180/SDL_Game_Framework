//
//  CollisionManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "collisionmanager.h"
#include "Collision.h"
#include "player.h"
//#include "TileLayer.h"

//void CollisionManager::checkPlayerEnemyBulletCollision(CPlayer* pPlayer)
//{
//    SDL_Rect* pRect1 = new SDL_Rect();
//    pRect1->x = pPlayer->GetPosition().getX();
//    pRect1->y = pPlayer->GetPosition().getY();
//    pRect1->w = pPlayer->getWidth();
//    pRect1->h = pPlayer->getHeight();
//    
//    for(int i = 0; i < TheBulletHandler::Instance()->getEnemyBullets().size(); i++)
//    {
//        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->getEnemyBullets()[i];
//        
//        SDL_Rect* pRect2 = new SDL_Rect();
//        pRect2->x = pEnemyBullet->GetPosition().getX();
//        pRect2->y = pEnemyBullet->GetPosition().getY();
//        
//        pRect2->w = pEnemyBullet->getWidth();
//        pRect2->h = pEnemyBullet->getHeight();
//        
//        if(RectRect(pRect1, pRect2))
//        {
//            if(!pPlayer->dying() && !pEnemyBullet->dying())
//            {
//                pEnemyBullet->collision();
//                pPlayer->collision();
//            }
//        }
//        
//        delete pRect2;
//    }
//    
//    delete pRect1;
//}
//
//void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<CGameObject *> &objects)
//{
//    for(int i = 0; i < objects.size(); i++)
//    {
//        CGameObject* pObject = objects[i];
//        
//        for(int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++)
//        {
//            if(pObject->type() != std::string("Enemy") || !pObject->updating())
//            {
//                continue;
//            }
//            
//            SDL_Rect* pRect1 = new SDL_Rect();
//            pRect1->x = pObject->GetPosition().getX();
//            pRect1->y = pObject->GetPosition().getY();
//            pRect1->w = pObject->getWidth();
//            pRect1->h = pObject->getHeight();
//            
//            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];
//            
//            SDL_Rect* pRect2 = new SDL_Rect();
//            pRect2->x = pPlayerBullet->GetPosition().getX();
//            pRect2->y = pPlayerBullet->GetPosition().getY();
//            pRect2->w = pPlayerBullet->getWidth();
//            pRect2->h = pPlayerBullet->getHeight();
//            
//            if(RectRect(pRect1, pRect2))
//            {
//                if(!pObject->dying() && !pPlayerBullet->dying())
//                {
//                    pPlayerBullet->collision();
//                    pObject->collision();
//                }
//                
//            }
//            
//            delete pRect1;
//            delete pRect2;
//        }
//    }
//}
//
//void CollisionManager::checkPlayerEnemyCollision(CPlayer* pPlayer, const std::vector<CGameObject*> &objects)
//{
//    SDL_Rect* pRect1 = new SDL_Rect();
//    pRect1->x = pPlayer->GetPosition().getX();
//    pRect1->y = pPlayer->GetPosition().getY();
//    pRect1->w = pPlayer->getWidth();
//    pRect1->h = pPlayer->getHeight();
//    
//    for(int i = 0; i < objects.size(); i++)
//    {
//        if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
//        {
//            continue;
//        }
//        
//        SDL_Rect* pRect2 = new SDL_Rect();
//        pRect2->x = objects[i]->GetPosition().getX();
//        pRect2->y = objects[i]->GetPosition().getY();
//        pRect2->w = objects[i]->getWidth();
//        pRect2->h = objects[i]->getHeight();
//        
//        if(RectRect(pRect1, pRect2))
//        {
//            if(!objects[i]->dead() && !objects[i]->dying())
//            {
//                pPlayer->collision();
//            }
//        }
//        
//        delete pRect2;
//    }
//    
//    delete pRect1;
//}
//
//void CollisionManager::checkPlayerTileCollision(CPlayer* pPlayer, const std::vector<TileLayer*>& collisionLayers)
//{
//    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
//    {
//        TileLayer* pTileLayer = (*it);
//        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
//        
//        Vector2D layerPos = pTileLayer->GetPosition();
//        
//        int x, y, tileColumn, tileRow, tileid = 0;
//        
//        x = layerPos.getX() / pTileLayer->getTileSize();
//        y = layerPos.getY() / pTileLayer->getTileSize();
//        
//        if(pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
//        {
//            tileColumn = ((pPlayer->GetPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
//            tileRow = ((pPlayer->GetPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
//            tileid = tiles[tileRow + y][tileColumn + x];
//        }
//        else if(pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
//        {
//            tileColumn = pPlayer->GetPosition().getX() / pTileLayer->getTileSize();
//            tileRow = pPlayer->GetPosition().getY() / pTileLayer->getTileSize();
//            tileid = tiles[tileRow + y][tileColumn + x];
//        }
//        
//        if(tileid != 0)
//        {
//            pPlayer->collision();
//        }
//    }
//}