#ifndef __GAME_TILE_H_
#define __GAME_TILE_H_
#include "Actor.h"
#include "Vector2.h"
class GameTile : Actor
{
	GameTile(const Maths::Vector2& a_v2Pos, const Maths::Vector2& a_v2Size, const char* a_sFileName, const bool a_canCollide);
};

#endif //__GAME_TILE_H_