#include "GameWall.h"
#include <iostream>
GameWall::GameWall()
{
}
GameWall::GameWall(const unsigned int a_x, const unsigned int a_y) : Actor("Wall","./images/world/crate.png",Maths::Vector2(64, 64), 
	Maths::Vector2(
		64 * a_x - 32,
		64 * a_y - 32
			)
	, true)
{
}
GameWall::GameWall(const Maths::Vector2& a_v2)
{
}
GameWall::~GameWall()
{
}