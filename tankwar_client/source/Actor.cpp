#include "Actor.h"
//\=================================================================================
//\ Constructors and Destructor
//\=================================================================================
Actor::Actor() : AABBCollider2D("") 
{
	iSprite_ = -1;
	//StartDrawing();
}

Actor::Actor(const Actor& a_actor) : AABBCollider2D("")
{
	*this = a_actor;
	//StartDrawing();
}

Actor::Actor(const char * sSpriteName, const Maths::Vector2 & a_v2Size, const Maths::Vector2 & a_v2Pos, const UG::SColour & a_colour, const bool & a_CanCollide, const float & a_bearingRadians, const bool & a_isAlive, const int iLayer)
	: AABBCollider2D("",a_v2Pos, a_v2Size, a_CanCollide)
{
	iSprite_ = UG::CreateSprite(sSpriteName, a_v2Size.x, a_v2Size.y);
	UG::MoveSprite(iSprite_, a_v2Pos.xy);
	UG::SetSpriteLayer(iSprite_, iLayer);
	//StartDrawing();
	UG::GetSpriteMatrix(iSprite_, m4Sprite_.values_);
	sFileName_ = sSpriteName;
}

Actor::~Actor()
{
}

void Actor::Update(const float a_fDeltaTime)
{
	//Maths::Vector2 pos = Maths::Vector2(m4Sprite_.values_[8], m4Sprite_.values_[9]);
	//pos *= v2Velocity_ * a_fDeltaTime;
	//m4Sprite_.SetT(Maths::Vector3(pos.x, pos.y, 0));
	UG::SetSpriteMatrix(iSprite_, m4Sprite_.values_);
	Maths::AABBCollider2D::SetPos(Maths::Vector2(m4Sprite_.values_[8], m4Sprite_.values_[9]));
}

void Actor::StartDrawing()
{
	if (iSprite_ > -1)
	{
		UG::DrawSprite(iSprite_);
	}
}
void Actor::StopDrawing()
{
	if (iSprite_ > -1)
	{
		UG::StopDrawingSprite(iSprite_);
	}
}

Maths::Vector2 Actor::GetPos()
{
	return Maths::AABBCollider2D::GetPos();
}

void Actor::SetPos(const Maths::Vector2 & a_v2Pos)
{
	Maths::AABBCollider2D::SetPos(Maths::Vector2(a_v2Pos));
	m4Sprite_.values_[12] = a_v2Pos.x;
	m4Sprite_.values_[13] = a_v2Pos.y;
}
//\=================================================================================
//\ Get and Set Direction
//\=================================================================================

Maths::Vector2 Actor::GetDir()
{
	return Maths::Vector2(m4Sprite_.GetY().x, m4Sprite_.GetY().y);
}

void Actor::SetDir(const float a_fAngle)
{
	Maths::Matrix4 rot = Maths::CreateRotationMatrix4AboutZ(a_fAngle);
	//rot.SetT(m4Sprite_.GetT());
	//m4Sprite_ = rot;
	m4Sprite_ = rot * m4Sprite_;
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
	return Maths::AABBCollider2D::GetSize();
}
void Actor::SetSize(const Maths::Vector2& a_v2Size)
{
	Maths::AABBCollider2D::SetSize(a_v2Size);
	iSprite_ = UG::CreateSprite(sFileName_, a_v2Size.x, a_v2Size.y);
	UG::SetSpriteMatrix(iSprite_, m4Sprite_.values_);
}

//\=================================================================================
//\ Get and Set isAlive
//\=================================================================================
bool Actor::IsAlive()
{
	return bIsAlive_;
}
void Actor::IsAlive(const bool& a_isAlive)
{
	bIsAlive_ = a_isAlive;
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
	m4Sprite_.Translate(a_v2Translation * a_fDeltaTime);
}

//\=================================================================================
//\ Get and set the value of isStatic_
//\=================================================================================
bool Actor::IsStatic() const
{
	return Maths::AABBCollider2D::IsStatic();
}
void Actor::IsStatic(const bool a_isStatic)
{
	Maths::AABBCollider2D::IsStatic(a_isStatic);
}

void Actor::SetSprite(const int a_spriteID)
{
	iSprite_ = iSprite_;
	UG::MoveSprite(iSprite_, GetPos().xy);
	UG::DrawSprite(iSprite_);
}

int Actor::GetSprite()const
{
	return iSprite_;
}

void Actor::TurnLeft(const float f, const float a_fDeltaTime)
{
	m4Sprite_.RotateAboutZ(f * a_fDeltaTime * rotAmount_);
}
void Actor::TurnRight(const float f, const float a_fDeltaTime)
{
	m4Sprite_.RotateAboutZ(-f * a_fDeltaTime * rotAmount_);
}