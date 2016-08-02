#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"

class Player : public Actor
{
	int score_ = 0;
	float rotAmount_ = 0.0001f;
	float turretCooldown = 0.0f;
	int ID_;

public:
	Actor* turret_;
	Player();
	Player(const float& other);
	Player(const UG::SColour& a_base, const UG::SColour& a_turret);
	virtual ~Player();

	void Update(const float a_fDeltaTime);

	void StartDrawing();
	void StopDrawing();

	void MoveForwards(float f, const float a_fDeltaTime);
	void MoveBackwards(float f, const float a_fDeltaTime);
	void TurnLeft(const float f, const float a_fDeltaTime);
	void TurnRight(const float f, const float a_fDeltaTime);
	float GetTurretCooldown();
	void SetTurretCooldown(float a_cooldown);

	//virtual Maths::Vector2 GetPos();
	//virtual void SetPos(const Maths::Vector2& a_v2Dir);

	void IncrementScore();
	int GetScore();

	int GetID() const;
	void SetID(const int a_ID);
};

#endif //__PLAYER_H_