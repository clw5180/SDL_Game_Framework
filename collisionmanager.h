//
//  collisionmanager.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__CollisionManager__
#define __SDL_Game_Programming_Book__CollisionManager__

#include <iostream>
#include <vector>

class CPlayer;
class CGameObject;
class TileLayer;

class CollisionManager
{
public:
    
    void checkPlayerEnemyBulletCollision(CPlayer* pPlayer);
    void checkPlayerEnemyCollision(CPlayer* pPlayer, const std::vector<CGameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<CGameObject*>& objects);
    void checkPlayerTileCollision(CPlayer* pPlayer, const std::vector<TileLayer*>& collisionLayers);
};

#endif /* defined(__SDL_Game_Programming_Book__CollisionManager__) */
