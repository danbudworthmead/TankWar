#include "Emitter.h"
Emitter::Emitter(Maths::Vector2 a_pos, Particle* a_pParticle, const char* a_sFilename, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds)
{

	particle_ = a_pParticle;
	filename_ = a_sFilename;
	pos_ = a_pos;
	frequency_ = a_uiFrequency;
	spreadRadians_ = a_fSpreadRadians;
	dir_ =Maths::Vector2(a_fDirectionRadians).GetNormalised();
	lifeTime_ = a_fLifeTimeSeconds;
}

Emitter::Emitter(Maths::Vector2 a_pos, Particle* a_pParticle, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds)
{
	particle_ = a_pParticle;
	pos_ = a_pos;
	frequency_ = a_uiFrequency;
	spreadRadians_ = a_fSpreadRadians;
	dir_ =Maths::Vector2(a_fDirectionRadians).GetNormalised();
	lifeTime_ = a_fLifeTimeSeconds;
}


Emitter::Emitter(Particle* a_pParticle, unsigned int a_uiFrequency, float a_fDirectionRadians, float a_fSpreadRadians, float a_fLifeTimeSeconds)
{
	particle_ = a_pParticle;
	frequency_ = a_uiFrequency;
	spreadRadians_ = a_fSpreadRadians;
	dir_ =Maths::Vector2(a_fDirectionRadians).GetNormalised();
	lifeTime_ = a_fLifeTimeSeconds;
}

Emitter::~Emitter()
{
	delete particle_;
	for (auto iter = particles_.begin(); iter != particles_.end(); ++iter)
	{
		Particle* p = (*iter);
		delete p;
	}
	particles_.clear();
}

void Emitter::Emit(const float a_lifeTime)
{
	aliveTime_ = 0;
	lifeTime_ = a_lifeTime;
}

int Emitter::GetParticleCount()
{
	return particles_.size();
}
int Emitter::Update(const float a_fDeltaTime)
{
	aliveTime_ += a_fDeltaTime;
	if (aliveTime_ <= lifeTime_ || lifeTime_ == -1)
	{
		for (int i = 0; i < frequency_; i++)
		{
			//particles_.push_back(new Particle(particle_,Maths::Vector2(dir_.Bearing() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / spreadRadians_)) - spreadRadians_ * 0.5f), pos_));
			
			particles_.push_back(new Particle(filename_, particle_->GetStartingColour(), particle_->GetEndingColour(), particle_->GetSize(),Maths::Vector2(dir_.Bearing() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / spreadRadians_)) - spreadRadians_ * 0.5f), pos_, particle_->GetLifeTimeSeconds(), particle_->GetSpeed()));
		}

		for (auto iter = particles_.begin(); iter != particles_.end(); )
		{
			Particle* p = (*iter);
			if (p->Update(a_fDeltaTime) == 0)
			{
				iter = particles_.erase(iter);
				delete p;
			}
			else
			{
				++iter;
			}
		}
		return 1;
	}
	
	for (auto iter = particles_.begin(); iter != particles_.end(); ++iter)
	{
		Particle* p = (*iter);
		p->StopDrawing();
	}

	return 0;
}

void Emitter::SetSpreadRadians(const float a_fSpreadRadians)
{
	spreadRadians_ = a_fSpreadRadians;
}

float Emitter::GetSpreadRadians() const
{
	return spreadRadians_;
}

void Emitter::SetDir(const Maths::Vector2& a_v2Dir)
{
	dir_ = a_v2Dir;
	dir_ = dir_.GetNormalised();
}

Maths::Vector2 Emitter::GetDir() const
{
	return dir_;
}

void Emitter::SetPos(const Maths::Vector2& a_v2Pos)
{
	pos_ = a_v2Pos;
}

Maths::Vector2 Emitter::GetPos() const
{
	return pos_;
}

void Emitter::SetParticle(const Particle& a_particle)
{
	particle_ = new Particle(a_particle);
}