#include "Player.h"
#include "Enumerations.h"
#include "XboxController.h"
#include <iostream>
Player::Player() : Actor("Player","./images/tank_base.png", Maths::Vector2(64, 64), Maths::Vector2(0, 0), false)
{
	//turret_ = new Turret();
	//turret_ = new Actor("Turret", "./images/tank_turret.png", Maths::Vector2(64, 64),Maths::Vector2(0, 0));
	turret_ = UG::CreateSprite("./images/tank_turret.png", 0, 0, true);
	//turret_->StartDrawing();
	SetSpeed(200.0f);
}
Player::Player(const float& other)
{
	*this = other;
}
Player::Player(const UG::SColour& a_base, const UG::SColour& a_turret) : Actor("Player", "./images/tank_base.png",Maths::Vector2(64, 64),Maths::Vector2(-100, -100), false, a_base)
{
	//turret_ = new Actor("Turret", "./images/tank_turret.png", Maths::Vector2(64, 64),Maths::Vector2(-100, -100), a_turret);.
	turret_ = UG::CreateSprite("./images/tank_turret.png", 0, 0, true);
	//turret_->StartDrawing();
	SetSpeed(200.0f);
}
Player::~Player(){}

void Player::Update(const float a_fDeltaTime, XboxController& a_pXboxController)
{
	XINPUT_GAMEPAD gamepad = a_pXboxController.GetState().Gamepad;

	Maths::Vector4 v4Fwd = m4Sprite_.GetY();

	float RT = gamepad.bRightTrigger / 255.0f;
	SetPos(GetPos() + Maths::Vector2(v4Fwd.x, v4Fwd.y) * a_fDeltaTime * RT * 100.f);
	
	float LT = gamepad.bLeftTrigger / 255.0f;
	SetPos(GetPos() - Maths::Vector2(v4Fwd.x, v4Fwd.y) * a_fDeltaTime * LT * 100.f);

	Maths::Vector2 LThumb(gamepad.sThumbLX, gamepad.sThumbLY);
	if (LThumb.Magnitude() > 30000)
	{
		float f = rotAmount_ * LThumb.x * a_fDeltaTime;
		m4Sprite_.RotateAboutZ(f);
		UG::RotateSprite(turret_, -f * (180/Maths::PI));
	}
	
	Maths::Vector2 RThumb(gamepad.sThumbRX, gamepad.sThumbRY);
	if (RThumb.Magnitude() > 30000)
	{
		UG::RotateSprite(turret_, -rotAmount_ * RThumb.x * a_fDeltaTime * (180 / Maths::PI));
	}

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
}

void Player::UpdateSprite()
{
	//Move base to collider2D
	m4Sprite_.SetPosition2D(AABBCollider2D::GetPos());

	//Move turret to my base
	UG::MoveSprite(turret_, m4Sprite_.GetPosition2D().x, m4Sprite_.GetPosition2D().y);

	Actor::Update();
}

void Player::StartDrawing()
{
	//if (turret_)
	//	turret_->StartDrawing();
	UG::DrawSprite(turret_);
	Actor::StartDrawing();
}
void Player::StopDrawing()
{
	//turret_->StopDrawing();
	UG::StopDrawingSprite(turret_);
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