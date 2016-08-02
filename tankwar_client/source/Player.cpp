#include "Player.h"
#include "Enumerations.h"
Player::Player() : Actor("./images/tank_base.png",Maths::Vector2(64, 64),Maths::Vector2(0, 0), UG::SColour(255, 255, 255, 255), true, 0, true)
{
	//turret_ = new Turret();
	turret_ = new Actor("./images/tank_base.png",Maths::Vector2(64, 64),Maths::Vector2(0, 0));
	SetSpeed(200.0f);
}
Player::Player(const float& other)
{
	*this = other;
}
Player::Player(const UG::SColour& a_base, const UG::SColour& a_turret) : Actor("./images/tank_base.png",Maths::Vector2(64, 64),Maths::Vector2(-100, -100), a_base, true, 0, false)
{
	turret_ = new Actor("./images/tank_turret.png",Maths::Vector2(64, 64),Maths::Vector2(-100, -100), a_turret);
	SetSpeed(200.0f);
}
Player::~Player(){}

void Player::Update(const float a_fDeltaTime)
{
	Actor::Update(a_fDeltaTime);

	/*
	//\=================================================================================
	//\ Keyboard Controls
	//\=================================================================================
	//Controlling the base of the tank
	if (UG::IsKeyDown(UG::KEY_W))
		MoveForwards();
	if (UG::IsKeyDown(UG::KEY_A))
		TurnLeft();
	if (UG::IsKeyDown(UG::KEY_S))
		MoveBackwards();
	if (UG::IsKeyDown(UG::KEY_D))
		TurnRight();

	//Rotating the turret to face the mouse
	turret_->SetDir(UG::GetMousePos() - GetPos());
	*/

	//Move turret to my base
	turret_->SetPos(GetPos());
	turret_->Update(a_fDeltaTime);

	//UG::SetSpriteMatrix(sprite, m4_.values_);
}

void Player::StartDrawing()
{
	if (turret_)
		turret_->StartDrawing();
	Actor::StartDrawing();
}
void Player::StopDrawing()
{
	turret_->StopDrawing();
	Actor::StopDrawing();
}

void Player::MoveForwards(float f, const float a_fDeltaTime)
{
	m4Sprite_.MoveForwards(f * a_fDeltaTime);
}
void Player::MoveBackwards(float f, const float a_fDeltaTime)
{
	m4Sprite_.MoveBackwards(f * a_fDeltaTime);
}
void Player::TurnLeft(const float f, const float a_fDeltaTime)
{
	m4Sprite_.RotateAboutZ(f * a_fDeltaTime * rotAmount_);
}
void Player::TurnRight(const float f, const float a_fDeltaTime)
{
	m4Sprite_.RotateAboutZ(-f * a_fDeltaTime * rotAmount_);
}
float Player::GetTurretCooldown()
{
	return turretCooldown;
}
void Player::SetTurretCooldown(float a_cooldown)
{
	turretCooldown = a_cooldown;
}
void Player::IncrementScore()
{
	score_++;
}
int Player::GetScore()
{
	return score_;
}

int Player::GetID() const
{
	return ID_;
}

void Player::SetID(const int a_ID)
{
	ID_ = a_ID;
}