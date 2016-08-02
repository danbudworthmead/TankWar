#ifndef __NETWORK_PLAYER_H_
#define __NETWORK_PLAYER_H_
#include "Vector2.h"
namespace UG
{
	class SColour;
}

class NetworkPlayer
{
	int baseSpriteID_, turretSpriteID_;
	Maths::Vector2 pos_;
	float baseRot_, turretRot_;
	bool isAlive_;
public:
	NetworkPlayer();

	void Update();

	void SetPos(const Maths::Vector2& a_v2Pos);
	Maths::Vector2 GetPos()const;

	void SetBaseRot(const float a_fBaseRot);
	float GetBaseRot()const;

	void SetTurretRot(const float a_fTurretRot);
	float GetTurretRot()const;

	void IsAlive(const bool a_isAlive);
	bool IsAlive()const;

	void SetColours(const UG::SColour& a_baseColour, const UG::SColour& a_turretColour);
};

#endif //__NETWORK_PLAYER_H_