/*
#include "WallCollider2D.h"
WallCollider2D::WallCollider2D() {}
WallCollider2D::WallCollider2D(const Maths::WallCollider2D& a_wall) 
{
	Set(a_wall.v2Start_, a_wall.v2End_);
}
WallCollider2D::WallCollider2D(const Maths::Vector2& a_v2Start, const Maths::Vector2& a_v2End) 
{
	Set(a_v2Start, a_v2End);
}
WallCollider2D::~WallCollider2D() {}
void Maths::WallCollider2D::SetStart(const Maths::Vector2& a_v2Start)
{
	Set(a_v2Start, v2End_);
}
Vector2 Maths::WallCollider2D::GetStart() const 
{
	return v2Start_;
}
void Maths::WallCollider2D::SetEnd(const Maths::Vector2& a_v2End)
{
	Set(v2Start_, a_v2End);
}
Vector2 Maths::WallCollider2D::GetEnd() const 
{
	return v2End_;
}
void Maths::WallCollider2D::Set(const Maths::Vector2& a_v2Start, const Maths::Vector2& a_v2End) 
{
	v2Start_ = a_v2Start;
	v2End_ = a_v2End;
	CalculateNormal();
}
void Maths::WallCollider2D::CalculateNormal() 
{
	v2Normal_ = (v2End_ - v2Start_).GetNormalised().PerpCCW();
}
Vector2 Maths::WallCollider2D::GetNormal() const
{
	return v2Normal_;
}
*/