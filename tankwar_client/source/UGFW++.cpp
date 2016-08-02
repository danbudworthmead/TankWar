#include "UGFW++.h"
namespace UG 
{
	//float spriteArray[16];
	//\=================================================================================
	//\ Set the rotation of a sprite in degrees
	//\=================================================================================
	void SetBearingDegrees(int a_uiSpriteID, float a_radians)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		spriteArray[0] = sin((a_radians + 90) * Maths::PI / 180);
		spriteArray[1] = cos((a_radians + 90) * Maths::PI / 180);
		spriteArray[4] = sin((a_radians)* Maths::PI / 180);
		spriteArray[5] = cos((a_radians)* Maths::PI / 180);
		SetSpriteMatrix(a_uiSpriteID, spriteArray);
	}

	//\=================================================================================
	//\ Set the rotation of a sprite in radians
	//\=================================================================================
	void SetBearingRadians(int a_uiSpriteID, float a_radians)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		spriteArray[0] = sin(a_radians + Maths::PI * 0.5f);
		spriteArray[1] = cos(a_radians + Maths::PI * 0.5f);
		spriteArray[4] = sin(a_radians);
		spriteArray[5] = cos(a_radians);
		SetSpriteMatrix(a_uiSpriteID, spriteArray);
	}

	//\=================================================================================
	//\ Get the rotation of a sprite in degrees as a float
	//\=================================================================================
	float GetBearingDegrees(int a_uiSpriteID)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		float f = (atan2(spriteArray[5], spriteArray[4]) * 180 / Maths::PI) - 90;
		if (f <= 90 && f >= 0)									 
			f -= 360;
		return abs(f);
	}

	//\=================================================================================
	//\ Get the rotation of a sprite in radians as a float
	//\=================================================================================
	float GetBearingRadians(int a_uiSpriteID)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		float f = (atan2(spriteArray[5], spriteArray[4])) - Maths::PI * 0.5f;
		if (f <= Maths::PI * 0.5f && f >= 0)
			f -= 2 * Maths::PI;
		return abs(f);
	}

	//\=================================================================================
	//\ Translate the sprite by a vector 2 from it's current position
	//\=================================================================================
	void TranslateSprite(int a_uiSpriteID, const Maths::Vector2& a_v2)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		spriteArray[12] += a_v2.x;
		spriteArray[13] += a_v2.y;
		SetSpriteMatrix(a_uiSpriteID, spriteArray);
	}

	//\=================================================================================
	//\ Translate the sprite by a vector 2 from it's current position
	//\=================================================================================
	void TranslateSprite(int a_uiSpriteID, const float& a_x, const float& a_y)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		spriteArray[12] += a_x;
		spriteArray[13] += a_y;
		SetSpriteMatrix(a_uiSpriteID, spriteArray);
	}

	//\=================================================================================
	//\ Set the sprites position with a 2D vector
	//\=================================================================================
	void SetSpritePos(int a_uiSpriteID, const Maths::Vector2& v2)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		spriteArray[12] = v2.x;
		spriteArray[13] = v2.y;
		SetSpriteMatrix(a_uiSpriteID, spriteArray);
	}

	//\=================================================================================
	//\ Get the sprites position in the world as a 2D vector
	//\=================================================================================
	Maths::Vector2 GetSpritePosition(int a_uiSpriteID)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		return Maths::Vector2(spriteArray[12], spriteArray[13]);
	}

	//\=================================================================================
	//\ Get the sprites X position in the world
	//\=================================================================================
	float GetSpriteXPos(int a_uiSpriteID)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		return spriteArray[12];
	}

	//\=================================================================================
	//\ Get the sprites Y position in the world
	//\=================================================================================
	float GetSpriteYPos(int a_uiSpriteID)
	{
		GetSpriteMatrix(a_uiSpriteID, spriteArray);
		return spriteArray[13];
	}

	//\=================================================================================
	//\ Get the sprites size as a 2D vector
	//\=================================================================================
	Maths::Vector2 GetSpriteSize(int a_uiSpriteID)
	{
		float x=0, y=0;
		UG::GetSpriteScale(a_uiSpriteID, x, y);
		return Maths::Vector2(x, y);
	}

	//\=================================================================================
	//\ Get the sprites X size in pixels
	//\=================================================================================
	float GetSpriteWidth(int a_uiSpriteID)
	{
		return 0;
	}

	//\=================================================================================
	//\ Get the sprites Y size in pixels
	//\=================================================================================
	float GetSpriteHeight(int a_uiSpriteID)
	{
		return 0;
	}

	//\=================================================================================
	//\ Check if a point is inside of a sprite
	//\=================================================================================
	bool IsPointInsideSprite(int a_uiSpriteID, const Maths::Vector2& a_v2)
	{
		Bounds bounds(a_uiSpriteID);
		if (a_v2.x < bounds.min.x)
			return false;
		if (a_v2.x > bounds.max.x)
			return false;
		if (a_v2.y < bounds.min.y)
			return false;
		if (a_v2.y > bounds.max.y)
			return false;
		return true;
		/*
		if (a_v2.x > bounds.min.x &&
			a_v2.x < bounds.max.x &&
			a_v2.y > bounds.min.y &&
			a_v2.y < bounds.max.y)
		{
			return true;
		}
		return false;
		*/
	}

	//\=================================================================================
	//\ Get the current key being pressed
	//\=================================================================================
	int GetKeyDown()
	{
		for (int i = 0; i < 200; i++)
		{
			if (UG::IsKeyDown(i))
			{
				return i;
			}
		}
	}

	//\=================================================================================
	//\ Return Mouse Position as a Vector 2
	//\=================================================================================
	Maths::Vector2 GetMousePos()
	{
		double x = 0, y = 0;
		GetMousePos(x, y);
		return Maths::Vector2(x, (const float)GetScreenSize().y - y);
	}

	//\=================================================================================
	//\ Return Screen Size as a Vector 2
	//\=================================================================================
	Maths::Vector2 GetScreenSize()
	{
		int x = 0, y = 0;
		GetScreenSize(x, y);
		return Maths::Vector2(x, y);
	}
}