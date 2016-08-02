#ifndef __PARTICLE_H_
#define __PARTICLE_H_
#include "Vector2.h"
#include "UGFW++.h"
#include <vector>
class Particle
{
	UG::SColour startingColour_, endingColour_, currentColour_;
	float aliveTime_, lifeTime_, speed_;
	Maths::Vector2 pos_, dir_, size_;
	int spriteID_;
	float currentPercentile_ = 0;
public:
	Particle(const char* a_filename, const UG::SColour a_uiStartingColour, const UG::SColour a_uiEndingColour, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Dir, const Maths::Vector2& a_v2Pos, const float a_fLifeTimeSeconds, const float a_fSpeed);
	Particle(const char* a_filename, const UG::SColour a_uiStartingColour, const UG::SColour a_uiEndingColour, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Dir, const float a_fLifeTimeSeconds, const float a_fSpeed);
	Particle(const Particle* a_pParticle);
	Particle(const Particle* a_pParticle, const Maths::Vector2& a_v2Dir, const Maths::Vector2& a_v2Pos);
	~Particle();

	int Update(const float a_fDeltaTime);
	UG::SColour GetStartingColour() const;
	UG::SColour GetEndingColour() const;
	Maths::Vector2 GetSize() const;
	Maths::Vector2 GetDir() const;
	Maths::Vector2 GetPos() const;
	float GetLifeTimeSeconds() const;
	float GetSpeed() const;
	void StopDrawing();
};

#endif //__PARTICLE_H_