/*
#ifndef __BOX_COLLIDER_2D_H_
#define __BOX_COLLIDER_2D_H_

#include "WallCollider2D.h"

class BoxCollider2D
{
	Maths::Vector2 pos_, size_, halfSize_;
	Maths::WallCollider2D walls_[4];
	bool wallsEnabled_[4];
	void UpdateWalls();
	void CalculateHalfSize();
public:
	BoxCollider2D();
	BoxCollider2D(const BoxCollider2D* a_other);
	BoxCollider2D(const BoxCollider2D& a_other);
	BoxCollider2D(const Maths::Vector2& a_v2Center, const Maths::Vector2& a_v2Size, const bool left = true, const bool top = true, const bool right = true, const bool bottom = true);
	void Set(const Maths::Vector2& a_v2Center, const Maths::Vector2& a_v2Size);
	void SetPos(const Maths::Vector2& a_v2Center);
	Maths::Vector2 GetPos() const;
	void SetSize(const Maths::Vector2& a_v2Size);
	Maths::Vector2 GetSize() const;
	friend bool BoxVsBox(const BoxCollider2D& lhs, const BoxCollider2D& rhs);
	Maths::Vector2 BoxVsBoxResponse(const BoxCollider2D& other, const float& a_speed);
	friend Maths::Vector2 BoxCollision(const BoxCollider2D& box, const BoxCollider2D& other, const float& speed);
	friend float DistanceToWall(const Maths::WallCollider2D& wall, const Maths::Vector2& v2);
	Maths::WallCollider2D GetWall(const int i);
	bool IsWallEnabled(const int i);
};

#endif //__BOX_COLLIDER_2D_H_
*/