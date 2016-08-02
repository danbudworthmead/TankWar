#include "NetworkPlayer.h"
#include "UGFW++.h"
NetworkPlayer::NetworkPlayer()
{
	baseSpriteID_ = UG::CreateSprite("./images/tank_base.png", 64, 64);
	turretSpriteID_ = UG::CreateSprite("./images/tank_turret.png", 64, 64);

	UG::DrawSprite(baseSpriteID_);
	UG::DrawSprite(turretSpriteID_);
}

void NetworkPlayer::Update()
{
	if (isAlive_)
	{
		UG::SetSpritePos(baseSpriteID_, pos_);
		UG::SetSpritePos(turretSpriteID_, pos_);

		UG::SetBearingRadians(baseSpriteID_, baseRot_);
		UG::SetBearingRadians(turretSpriteID_, turretRot_);
	}
}

void NetworkPlayer::SetPos(const Maths::Vector2& a_v2Pos)
{
	pos_ = a_v2Pos;
}

Maths::Vector2 NetworkPlayer::GetPos()const
{
	return pos_;
}

void NetworkPlayer::SetBaseRot(const float a_fBaseRot)
{
	baseRot_ = a_fBaseRot;
}

float NetworkPlayer::GetBaseRot()const
{
	return baseRot_;
}

void NetworkPlayer::SetTurretRot(const float a_fTurretRot)
{
	turretRot_ = a_fTurretRot;
}

float NetworkPlayer::GetTurretRot()const
{
	return turretRot_;
}

void NetworkPlayer::IsAlive(const bool a_isAlive)
{
	isAlive_ = a_isAlive;
}

bool NetworkPlayer::IsAlive()const
{
	return isAlive_;
}

void NetworkPlayer::SetColours(const UG::SColour& a_baseColour, const UG::SColour& a_turretColour)
{
	UG::SetSpriteColour(baseSpriteID_, a_baseColour);
	UG::SetSpriteColour(turretSpriteID_, a_turretColour);
}