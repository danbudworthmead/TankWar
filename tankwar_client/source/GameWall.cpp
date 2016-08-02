#include "GameWall.h"
#include <iostream>
GameWall::GameWall()
{
}
GameWall::GameWall(const unsigned int a_x, const unsigned int a_y) : Actor("./images/world/crate.png",Maths::Vector2(64, 64), 
	Maths::Vector2(
		64 * a_x - 32,
		64 * a_y - 32
			)
	, UG::SColour(255, 255, 255, 255), true)
{
}
GameWall::GameWall(const Maths::Vector2& a_v2)
{
}
GameWall::~GameWall()
{
}