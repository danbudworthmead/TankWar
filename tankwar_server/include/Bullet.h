#ifndef __BULLET_H_
#define __BULLET_H_
#include "Vector2.h"
class Bullet 
{
	Vector2 pos_, dir_;
public:
	Bullet(const Vector2& a_v2Pos, const Vector2& a_v2Dir);
	~Bullet();
	void Update();
};

#endif //__BULLET_H_