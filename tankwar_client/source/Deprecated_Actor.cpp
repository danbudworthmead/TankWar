/*
#include "Actor.h"
//\=================================================================================
//\ Constructors and Destructor
//\=================================================================================
Actor::Actor(){}
Actor::Actor(const Actor& a_actor)
{
	*this = a_actor;
}
Actor::Actor(const char* sSpriteName, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Pos, const UG::SColour& a_colour, const bool& a_CanCollide, const float& a_bearingRadians, const bool& a_isAlive)
{
	spriteID_ = UG::CreateSprite(sSpriteName, a_v2Size.x, a_v2Size.y, true, a_colour);
	UG::MoveSprite(spriteID_, a_v2Pos.x, a_v2Pos.y);
	isAlive_ = a_isAlive;
	if (a_CanCollide) 
	{ 
		pBoxCollider2D_ = new BoxCollider2D(a_v2Pos, a_v2Size); 
	}
	UG::GetSpriteMatrix(spriteID_, m4_.values_);
}
Actor::~Actor()
{
	delete pBoxCollider2D_;
}

bool Actor::HasCollided(const Actor& other)
{
	if (pBoxCollider2D_ == nullptr)
		return false;

	if (other.pBoxCollider2D_ == nullptr)
		return false;

	return BoxVsBox(*pBoxCollider2D_, *other.pBoxCollider2D_);
}

void Actor::Update()
{
	if (isAlive_)
	{
		if (pBoxCollider2D_)
			pBoxCollider2D_->SetPos(Maths::Vector2(m4_.GetT().x, m4_.GetT().y));
		UG::SetSpriteMatrix(spriteID_, m4_.values_);
	}
}
void Actor::StartDrawing()
{
	if (spriteID_ > -1)
	{
		UG::DrawSprite(spriteID_);
	}
}
void Actor::StopDrawing()
{
	if (spriteID_ > -1)
	{
		UG::StopDrawingSprite(spriteID_);
	}
}

//\=================================================================================
//\ Get a pointer to BoxCollider
//\=================================================================================
BoxCollider2D* Actor::GetBoxCollider()
{
	return pBoxCollider2D_;
}

//\=================================================================================
//\ Get and Set Position
//\=================================================================================
Maths::Vector2 Actor::GetPos()
{
	Maths::Vector4 v4 = m4_.GetT();
	return Maths::Vector2(v4.x, v4.y);
}
void Actor::SetPos(const Maths::Vector2& a_v2Pos)
{
	Maths::Vector4 v4 = m4_.GetT();
	v4.x = a_v2Pos.x;
	v4.y = a_v2Pos.y;
	m4_.SetT(v4);
}

//\=================================================================================
//\ Get and Set Direction
//\=================================================================================
Maths::Vector2 Actor::GetDir()
{
	return Maths::Vector2(m4_.GetY().x, m4_.GetY().y);
}
void Actor::SetDir(const float a_fAngle)
{
	Maths::Matrix4 rot = Maths::CreateRotationMatrix4AboutZ(a_fAngle);
	rot.SetT(m4_.GetT());
	m4_ = rot;
}

void Actor::SetDir(const Maths::Vector2 a_v2)
{
	SetDir(a_v2.Bearing());
}

//\=================================================================================
//\ Get and Set Size
//\=================================================================================
Maths::Vector2 Actor::SetSize()
{
	return size_;
}
void Actor::SetSize(const Maths::Vector2& a_v2Size)
{
	size_ = a_v2Size;
}

//\=================================================================================
//\ Get and Set isAlive
//\=================================================================================
bool Actor::IsAlive()
{
	return isAlive_;
}
void Actor::IsAlive(const bool& a_isAlive)
{
	isAlive_ = a_isAlive;
}

//\=================================================================================
//\ Get and Set speed
//\=================================================================================
float Actor::GetSpeed()
{
	return speed_;
}
void Actor::SetSpeed(const float& a_fSpeed)
{
	speed_ = a_fSpeed;
}

//\=================================================================================
//\ Translate the Actor
//\=================================================================================
void Actor::Translate(const Maths::Vector2& a_v2Translation, const float a_fDeltaTime)
{
	m4_.Translate(a_v2Translation * a_fDeltaTime);
	if (pBoxCollider2D_)
		pBoxCollider2D_->SetPos(Maths::Vector2(m4_.GetT().x, m4_.GetT().y));
}

//\=================================================================================
//\ Get and set the value of isStatic_
//\=================================================================================
bool Actor::IsStatic() const
{
	return isStatic_;
}
void Actor::IsStatic(const bool a_isStatic)
{
	isStatic_ = a_isStatic;
}

//\=================================================================================
//\ Axis Alligned Bounding Box Collision
//\=================================================================================
void AABBvsAABB(Actor* lhs, Actor* rhs, const float a_fDeltaTime)
{
	if (lhs->isAlive_ && rhs->isAlive_)
	{
		if (BoxVsBox(lhs->GetBoxCollider(), rhs->GetBoxCollider()))
		{
			lhs->Update();
			rhs->Update();
			float distNearestWall = ULLONG_MAX;
			int iClosest = -1;
			
			for (int i = 0; i < 4; i++)
			{
				if (!lhs->GetBoxCollider()->IsWallEnabled(i))
				{
					continue;
				}
				float distToWall = Maths::DistanceToWall(lhs->GetBoxCollider()->GetWall(i), rhs->GetPos());
				if (distToWall < distNearestWall)
				{
					distNearestWall = distToWall;
					iClosest = i;
				}
			}
			//translating the player by the closest walls normal vector + half the size of the wall
			lhs->Translate(rhs->GetBoxCollider()->GetWall(iClosest).GetNormal() * (distNearestWall + 32), 1); //I know this is really unoptimised
		}
	}
}

#include <iostream>
void Actor::SetSprite(const int a_spriteID)
{
	//UG::StopDrawingSprite(spriteID_);
	//UG::DestroySprite(spriteID_);
	std::cout << spriteID_ << "\t";
	spriteID_ = a_spriteID;
	std::cout << spriteID_ << "\n";
	UG::MoveSprite(spriteID_, GetPos().xy);
	UG::DrawSprite(spriteID_);
}

int Actor::GetSprite()const
{
	return spriteID_;
}
*/