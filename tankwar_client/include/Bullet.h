#ifndef __BULLET_H_
#define __BULLET_H_
#include "Actor.h"
#include <vector>

class Bullet : public Actor
{
	float aliveTimer_ = 4;
public:
	Bullet(const Maths::Vector2& a_pos, const Maths::Vector2& a_dir);
	~Bullet();

	int Update(std::vector<Bullet*> a_bullets, const float a_fDeltaTime);
};

#endif //__BULLET_H_