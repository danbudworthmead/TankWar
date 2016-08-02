#ifndef __EMITTER_H_
#define __EMITTER_H_
#include "Particle.h"
#include "Vector2.h"
class Emitter
{
	std::vector<Particle*> particles_;
	Particle* particle_;
	const char* filename_;
	unsigned int frequency_;
	float aliveTime_, lifeTime_, spreadRadians_;
	Maths::Vector2 pos_, dir_;
public:
	Emitter(Maths::Vector2 a_pos, Particle* a_pParticle, const char* a_sFilename, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds);
	Emitter(Maths::Vector2 a_pos, Particle* a_pParticle, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds);
	Emitter(Particle* a_pParticle, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds);
	~Emitter();

	int Update(const float a_fDeltaTime);
	int GetParticleCount();
	void SetSpreadRadians(const float a_fSpreadRadians);
	float GetSpreadRadians() const;
	void SetDir(const Maths::Vector2& a_v2Dir);
	Maths::Vector2 GetDir() const;
	void SetPos(const Maths::Vector2& a_v2Pos);
	Maths::Vector2 GetPos() const;
	void Emit(const float a_lifeTime);

	void SetParticle(const Particle& a_particle);
};

#endif //__EMITTER_H_