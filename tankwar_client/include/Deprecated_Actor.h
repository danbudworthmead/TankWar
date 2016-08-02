/*
#ifndef __ACTOR_H_
#define __ACTOR_H_

#include "Vector2.h"
#include "BoxCollider2D.h"
#include "UGFW++.h"

class Actor
{
protected:
	Maths::Vector2 size_;
	Maths::AABBCollider2D* pBoxCollider2D_ = nullptr;
	bool isAlive_ = false;
	int spriteID_ = -1;
	float speed_;
	bool isStatic_ = true;
protected:
	Maths::Matrix4 m4_;
public:
	//\=================================================================================
	//\ Constructors and Destructor
	//\=================================================================================
	Actor();
	Actor(const Actor& a_actor);
	Actor(const char* sSpriteName, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Pos, const UG::SColour& a_colour = UG::SColour(255, 255, 255, 255), const bool& a_CanCollide = false, const float& a_bearingRadians = 0.0f, const bool& a_isAlive = true);
	virtual ~Actor();

	virtual void Update();
	virtual void StartDrawing();
	virtual void StopDrawing();

	bool HasCollided(const Actor& other);
	
	//\=================================================================================
	//\ Get a pointer to BoxCollider
	//\=================================================================================
	BoxCollider2D* GetBoxCollider();

	//\=================================================================================
	//\ Get and Set Position
	//\=================================================================================
	virtual Maths::Vector2 GetPos();
	virtual void SetPos(const Maths::Vector2& a_v2Pos);

	//\=================================================================================
	//\ Get and Set Direction
	//\=================================================================================
	virtual Maths::Vector2 GetDir();
	virtual void SetDir(const float a_fAngle);
	virtual void SetDir(const Maths::Vector2 a_v2);

	//\=================================================================================
	//\ Get and Set Size
	//\=================================================================================
	Maths::Vector2 SetSize();
	void SetSize(const Maths::Vector2& a_v2Size);

	//\=================================================================================
	//\ Get and Set isAlive
	//\=================================================================================
	bool IsAlive();
	void IsAlive(const bool& a_isAlive);

	//\=================================================================================
	//\ Get and Set speed
	//\=================================================================================
	float GetSpeed();
	void SetSpeed(const float& a_fSpeed);
	
	//\=================================================================================
	//\ Translate the Actor
	//\=================================================================================
	void Translate(const Maths::Vector2& a_v2Translation, const float a_fDeltaTime);

	//\=================================================================================
	//\ Get and set the value of isStatic_
	//\=================================================================================
	bool IsStatic() const;
	void IsStatic(const bool a_isStatic);

	//\=================================================================================
	//\ Axis Alligned Bounding Box Collision
	//\=================================================================================
	friend void AABBvsAABB(Actor* lhs, Actor* rhs, const float a_fDeltaTime);
	
	//\=================================================================================
	//\ Set Sprite
	//\=================================================================================
	void SetSprite(const int a_spriteID);
	int GetSprite()const;
};

#endif //__ACTOR_H_
*/