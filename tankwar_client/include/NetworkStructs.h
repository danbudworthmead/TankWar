#ifndef __NETWORK_STRUCTS_H_
#define __NETWORK_STRUCTS_H_

#include "Vector2.h"

struct NetworkPlayerData
{
	Vector2 v2Position;
	float fHullBearing;
	float fTurretBearing;
};

#endif //__NETWORK_STRUCTS_H_