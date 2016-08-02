/*
#ifndef __WALL_COLLIDER_2D_H_
#define __WALL_COLLIDER_2D_H_

#include "Vector2.h"

class Maths::WallCollider2D
{
	Vector2 v2Start_, v2End_, v2Normal_;
	void CalculateNormal();
public:
	WallCollider2D();
	WallCollider2D(const Maths::WallCollider2D& a_wall);
	WallCollider2D(const Maths::Vector2& a_v2Start, const Maths::Vector2& a_v2End);
	~WallCollider2D();

	void SetStart(const Maths::Vector2& a_v2Start);
	Vector2 GetStart() const;

	void SetEnd(const Maths::Vector2& a_v2End);
	Vector2 GetEnd() const;

	Vector2 GetNormal() const;

	void Set(const Maths::Vector2& a_v2Start, const Maths::Vector2& a_v2End);
};

#endif //__WALL_COLLIDER_2D_H_
*/