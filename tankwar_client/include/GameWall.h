#ifndef __BLOCK_H_
#define __BLOCK_H_

#include "Actor.h"

class GameWall : public Actor
{
public:
	GameWall();
	GameWall(const unsigned int a_x, const unsigned int a_y);
	GameWall(const Maths::Vector2& a_v2);
	~GameWall();
};

#endif //__BLOCK_H_