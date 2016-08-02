#include "Bullet.h"
Bullet::Bullet(const Maths::Vector2& a_pos, const Maths::Vector2& a_dir) : Actor("./images/bullet.png",Maths::Vector2(8, 8), a_pos, UG::SColour(255, 255, 255, 255), true)
{
	Maths::Matrix4 rot = Maths::CreateRotationMatrix4AboutZ(-a_dir.Bearing());
	rot.SetT(m4Sprite_.GetT());
	m4Sprite_ = rot;
	SetSpeed(300.0f);
	Actor::StartDrawing();
}
Bullet::~Bullet() {}
#include <iostream>
int Bullet::Update(std::vector<Bullet*> a_bullets, const float a_fDeltaTime)
{
	if (IsAlive())
	{
		if (aliveTimer_ <= 0)
		{
			for (int i = 0; i < a_bullets.size(); i++)
			{
				if (a_bullets[i] == this)
				{
					Actor::StopDrawing();
					IsAlive(0);
					return i;
				}
			}
		}
		else
		{
			aliveTimer_ -= UG::GetDeltaTime();
			Maths::Vector4 v4 = m4Sprite_.GetY();
			m4Sprite_.Translate(Maths::Vector2(v4.x, v4.y) * GetSpeed() * a_fDeltaTime);
			Actor::Update(a_fDeltaTime);
		}
	}
	return -1;
}