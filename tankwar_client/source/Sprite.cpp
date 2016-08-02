#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const char* a_spriteName, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Pos)
{
	sprite_ = UG::CreateSprite(a_spriteName, a_v2Size.x, a_v2Size.y);
	UG::MoveSprite(sprite_, a_v2Pos.x, a_v2Pos.y);
	size_ = a_v2Size;
}
bool Sprite::IsInsideMe(const Maths::Vector2& a_v2)
{
	UG::Bounds bounds(sprite_);
	if (a_v2.x > UG::GetSpriteXPos(sprite_) - size_.x * 0.5f &&
		a_v2.x < UG::GetSpriteXPos(sprite_) + size_.x * 0.5f &&
		a_v2.y > UG::GetSpriteXPos(sprite_) - size_.y * 0.5f - size_.y &&
		a_v2.y < UG::GetSpriteXPos(sprite_) + size_.y * 0.5f - size_.y)
	{
		return true;
	}
	return false;
	//return UG::IsPointInsideSprite(sprite_, a_v2);
}