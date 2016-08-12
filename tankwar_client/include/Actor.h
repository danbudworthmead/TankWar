#ifndef __ACTOR_H_
#define __ACTOR_H_
#include "AABBCollider2D.h"
#include "UGFW++.h"
class Actor : public Maths::AABBCollider2D
{
	bool bIsAlive_;
	int iSprite_ = -1;
	float speed_;
	const char* sFileName_;
protected:
	float rotAmount_ = 0.0001f;
public:
	Maths::Matrix4 m4Sprite_;
	Actor();
	Actor(const Actor& a_actor);
	Actor(const char* a_actorName, const char* sSpriteName, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Pos, const bool & a_isStatic, const UG::SColour& a_colour = UG::SColour(255, 255, 255, 255), const float& a_bearingRadians = 0.0f, const bool& a_isAlive = true, const int iLayer=0);
	virtual ~Actor();

	virtual void Update(const float a_fDeltaTime);
	virtual void StartDrawing();
	virtual void StopDrawing();

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
	//\ Set Sprite
	//\=================================================================================
	void SetSprite(const int a_spriteID);
	int GetSprite()const;


	void TurnLeft(const float f, const float a_fDeltaTime);
	void TurnRight(const float f, const float a_fDeltaTime);
};

#endif //__ACTOR_H_