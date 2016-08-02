#ifndef __UGFWPLUS_H_
#define __UGFWPLUS_H_
#include "UGFW.h"
#include "mathLib.h"
namespace UG
{
	//\=================================================================================
	//\ Set the rotation of a sprite in degrees
	//\=================================================================================
	void SetBearingDegrees(int a_uiSpriteID, float a_degrees);

	//\=================================================================================
	//\ Set the rotation of a sprite in radians
	//\=================================================================================
	void SetBearingRadians(int a_uiSpriteID, float a_radians);

	//\=================================================================================
	//\ Get the rotation of a sprite in degrees as a float
	//\=================================================================================
	float GetBearingDegrees(int a_uiSpriteID);

	//\=================================================================================
	//\ Get the rotation of a sprite in radians as a float
	//\=================================================================================
	float GetBearingRadians(int a_uiSpriteID);

	//\=================================================================================
	//\ Translate the sprite by a vector 2 from it's current position
	//\=================================================================================
	void TranslateSprite(int a_uiSpriteID, const Maths::Vector2& a_v2);
	void TranslateSprite(int a_uiSpriteID, const float& a_x, const float& a_y);

	//\=================================================================================
	//\ Get the sprites position in the world as a 2D vector
	//\=================================================================================
	Maths::Vector2 GetSpritePosition(int a_uiSpriteID);

	//\=================================================================================
	//\ Set the sprites position with a 2D vector
	//\=================================================================================
	void SetSpritePos(int a_uiSpriteID, const Maths::Vector2& v2);

	//\=================================================================================
	//\ Get the sprites X position in the world
	//\=================================================================================
	float GetSpriteXPos(int a_uiSpriteID);

	//\=================================================================================
	//\ Get the sprites Y position in the world
	//\=================================================================================
	float GetSpriteYPos(int a_uiSpriteID);

	//\=================================================================================
	//\ Get the sprites size as a 2D vector
	//\=================================================================================
	Maths::Vector2 GetSpriteSize(int a_uiSpriteID);

	//\=================================================================================
	//\ Get the sprites X size in pixels
	//\=================================================================================
	float GetSpriteWidth(int a_uiSpriteID);

	//\=================================================================================
	//\ Get the sprites Y size in pixels
	//\=================================================================================
	float GetSpriteHeight(int a_uiSpriteID);

	//\=================================================================================
	//\ Check if a point is inside of a sprite
	//\=================================================================================
	bool IsPointInsideSprite(int a_uiSpriteID, const Maths::Vector2& a_v2);
	
	//\=================================================================================
	//\ Get the current key being pressed
	//\=================================================================================
	int GetKeyDown();

	//\=================================================================================
	//\ Return Mouse Position as a Vector 2
	//\=================================================================================
	Maths::Vector2 GetMousePos();

	//\=================================================================================
	//\ Return Screen Size as a Vector 2
	//\=================================================================================
	Maths::Vector2 GetScreenSize();

	struct Bounds
	{
		Bounds(float a_minx, float a_maxx, float a_miny, float a_maxy)
		{
			min =Maths::Vector2(a_minx, a_miny);
			max =Maths::Vector2(a_maxx, a_maxy);
		}
		Bounds(int a_uiSpriteID)
		{
			min.x = GetSpriteXPos(a_uiSpriteID) - GetSpriteWidth(a_uiSpriteID) * 0.5f;
			max.x = GetSpriteXPos(a_uiSpriteID) + GetSpriteWidth(a_uiSpriteID) * 0.5f;
			min.y = GetSpriteYPos(a_uiSpriteID) - GetSpriteHeight(a_uiSpriteID) * 0.5f;
			max.y = GetSpriteYPos(a_uiSpriteID) + GetSpriteHeight(a_uiSpriteID) * 0.5f;
		}
		Maths::Vector2 min;
		Maths::Vector2 max;
	};

	static float spriteArray[16];
}
#endif //__UGFWPLUS_H_