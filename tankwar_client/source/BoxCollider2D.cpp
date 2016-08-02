/*
#include "BoxCollider2D.h"
#include "UGFW.h"
BoxCollider2D::BoxCollider2D()
{
}
BoxCollider2D::BoxCollider2D(const BoxCollider2D& a_other)
{
	Set(a_other.pos_, a_other.size_);
}
BoxCollider2D::BoxCollider2D(const BoxCollider2D* a_other)
{
	Set(a_other->pos_, a_other->size_);
}
BoxCollider2D::BoxCollider2D(const Maths::Vector2& a_v2Center, const Maths::Vector2& a_v2Size, const bool left, const bool top, const bool right, const bool bottom)
{
	wallsEnabled_[0] = left;
	wallsEnabled_[1] = top;
	wallsEnabled_[2] = right;
	wallsEnabled_[3] = bottom;
	Set(a_v2Center, a_v2Size);
}
void BoxCollider2D::Set(const Maths::Vector2& a_v2Center, const Maths::Vector2& a_v2Size)
{
	pos_ = a_v2Center;
	size_ = a_v2Size;
	CalculateHalfSize();
	UpdateWalls();
}
void BoxCollider2D::SetPos(const Maths::Vector2& a_v2Center)
{
	Set(a_v2Center, size_);
}
Maths::Vector2 BoxCollider2D::GetPos() const
{
	return pos_;
}
void BoxCollider2D::SetSize(const Maths::Vector2& a_v2Size)
{
	Set(pos_, a_v2Size);
}
Maths::Vector2 BoxCollider2D::GetSize() const
{
	return size_;
}
//Private Methods
void BoxCollider2D::UpdateWalls()
{
	float minX = pos_.x - halfSize_.x;
	float maxX = pos_.x + halfSize_.x;
	float minY = pos_.y - halfSize_.y;
	float maxY = pos_.y + halfSize_.y;
	walls_[0].Set(Maths::Vector2(minX, minY), Maths::Vector2(minX, maxY));
	walls_[1].Set(Maths::Vector2(minX, maxY), Maths::Vector2(maxX, maxY));
	walls_[2].Set(Maths::Vector2(maxX, maxY), Maths::Vector2(maxX, minY));
	walls_[3].Set(Maths::Vector2(maxX, minY), Maths::Vector2(minX, minY));
}
void BoxCollider2D::CalculateHalfSize()
{
	halfSize_ = size_ * 0.5f;
}
bool BoxVsBox(const BoxCollider2D& lhs, const BoxCollider2D& rhs)
{
	if (lhs.pos_.x + lhs.halfSize_.x < rhs.pos_.x - rhs.halfSize_.x)
		return false;
	if (lhs.pos_.x - lhs.halfSize_.x > rhs.pos_.x + rhs.halfSize_.x)
		return false;
	if (lhs.pos_.y + lhs.halfSize_.y < rhs.pos_.y - rhs.halfSize_.y)
		return false;
	if (lhs.pos_.y - lhs.halfSize_.y > rhs.pos_.y + rhs.halfSize_.y)
		return false;
	return true;
}
Vector2 BoxCollider2D::BoxVsBoxResponse(const BoxCollider2D& other, const float& a_speed)
{
	if (BoxVsBox(*this, other))
	{
		float distNearestWall = ULLONG_MAX;
		int iClosest = -1;
		for (int i = 0; i < sizeof(walls_) / sizeof(WallCollider2D); i++)
		{
			float distToWall = DotProd(other.pos_ - walls_[i].GetStart(), walls_[i].GetNormal());
			if (distToWall < distNearestWall)
			{
				distNearestWall = distToWall;
				iClosest = i;
			}
		}
		if (iClosest != -1) // just make sure we don't accidently go outside the array
		{
			return other.pos_ + walls_[iClosest].GetNormal().PerpCCW().PerpCCW() * a_speed * UG::GetDeltaTime(); // return just enough to be away from the closest wall and for some reason flip it 180 degrees
		}
	}
	return pos_;
}
#include <iostream>
Vector2 BoxCollision(const BoxCollider2D& box, const BoxCollider2D& other, const float& speed)
{
	if (BoxVsBox(box, other))
	{
		float distNearestWall = ULLONG_MAX;
		int iClosest = -1;
		for (int i = 0; i < sizeof(box.walls_) / sizeof(WallCollider2D); i++)
		{
			float distToWall = DistanceToWall(box.walls_[i], other.pos_);
			if (distToWall < distNearestWall)
			{
				distNearestWall = distToWall;
				iClosest = i;
			}
		}
		if (iClosest != -1) // just make sure we don't accidently go outside the array
		{
			return other.pos_ + box.walls_[iClosest].GetNormal().PerpCCW().PerpCCW() * speed * UG::GetDeltaTime(); // return just enough to be away from the closest wall and for some reason flip it 180 degrees
		}
	}
	return other.pos_; //let's not change our position if there's no collision...
}

float DistanceToWall(const Maths::WallCollider2D& wall, const Maths::Vector2& v2)
{
	return DotProd(v2 - wall.GetStart(), wall.GetNormal());
}

WallCollider2D BoxCollider2D::GetWall(const int i)
{
	return walls_[i];
}

bool BoxCollider2D::IsWallEnabled(const int i)
{
	return wallsEnabled_[i];
}
*/