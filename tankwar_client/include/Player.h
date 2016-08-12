#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Actor.h"
class XboxController;
class Player : public Actor
{
	int score_ = 0;
	float turretCooldown = 0.0f;
	int ID_;

public:
	//Actor* turret_;
	int turret_;
	Player();
	Player(const float& other);
	Player(const UG::SColour& a_base, const UG::SColour& a_turret);
	virtual ~Player();

	void Update(const float a_fDeltaTime, XboxController& a_pXboxController);

	void StartDrawing();
	void StopDrawing();

	void MoveForwards(float f, const float a_fDeltaTime);
	void MoveBackwards(float f, const float a_fDeltaTime);
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