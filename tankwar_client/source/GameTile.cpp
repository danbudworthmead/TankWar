#include "GameTile.h"

GameTile::GameTile(const Maths::Vector2& a_v2Pos, const Maths::Vector2& a_v2Size, const char* a_sFileName, const bool a_isStatic)
	: Actor("Wall", a_sFileName, a_v2Size, a_v2Pos, a_isStatic)
{

}
