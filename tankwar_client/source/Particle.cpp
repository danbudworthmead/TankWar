#include "Particle.h"
Particle::Particle(const char* a_filename, const UG::SColour a_uiStartingColour, const UG::SColour a_uiEndingColour, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Dir, const Maths::Vector2& a_v2Pos, const float a_fLifeTimeSeconds, const float a_fSpeed)
{
	spriteID_				= UG::CreateSprite(a_filename, a_v2Size.x, a_v2Size.y, true, startingColour_);
	dir_					= a_v2Dir;
	dir_					= dir_.GetNormalised();
	size_					= a_v2Size;
	aliveTime_				= 0.f;
	lifeTime_				= a_fLifeTimeSeconds;
	speed_					= a_fSpeed;
	startingColour_			= a_uiStartingColour;
	endingColour_			= a_uiEndingColour;
	pos_					= a_v2Pos;
	UG::SetBearingRadians(spriteID_, a_v2Dir.Bearing());
	UG::SetSpritePos(spriteID_, pos_);
	UG::SetSpriteColour(spriteID_, a_uiStartingColour);
	UG::DrawSprite(spriteID_);
}

Particle::Particle(const char* a_filename, const UG::SColour a_uiStartingColour, const UG::SColour a_uiEndingColour, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Dir, const float a_fLifeTimeSeconds, const float a_fSpeed)
{
	spriteID_ = UG::CreateSprite(a_filename, a_v2Size.x, a_v2Size.y, true, startingColour_);
	dir_ = a_v2Dir;
	dir_ = dir_.GetNormalised();
	size_ = a_v2Size;
	aliveTime_ = 0.f;
	lifeTime_ = a_fLifeTimeSeconds;
	speed_ = a_fSpeed;
	startingColour_ = a_uiStartingColour;
	endingColour_ = a_uiEndingColour;
	UG::SetBearingRadians(spriteID_, a_v2Dir.Bearing());
	UG::SetSpritePos(spriteID_, pos_);
	UG::SetSpriteColour(spriteID_, a_uiStartingColour);
	UG::DrawSprite(spriteID_);
}

Particle::Particle(const Particle* a_pParticle)
{
	spriteID_				= UG::DuplicateSprite(a_pParticle->spriteID_);
	dir_					= a_pParticle->dir_;
	dir_					= dir_.GetNormalised();
	size_					= a_pParticle->size_;
	aliveTime_				= 0.f;
	lifeTime_				= a_pParticle->lifeTime_;
	speed_					= a_pParticle->speed_;
	startingColour_			= a_pParticle->startingColour_;
	endingColour_			= a_pParticle->endingColour_;
	pos_					= a_pParticle->pos_;
	UG::SetBearingRadians(spriteID_, a_pParticle->dir_.Bearing());
	UG::SetSpritePos(spriteID_, pos_);
	UG::DrawSprite(spriteID_);
}

Particle::Particle(const Particle* a_pParticle, const Maths::Vector2& a_v2Dir, const Maths::Vector2& a_v2Pos)
{
	spriteID_				= UG::DuplicateSprite(a_pParticle->spriteID_);
	dir_					= a_v2Dir;
	dir_					= dir_.GetNormalised();
	size_					= a_pParticle->size_;
	aliveTime_				= 0.f;
	lifeTime_				= a_pParticle->lifeTime_;
	speed_					= a_pParticle->speed_;
	startingColour_			= a_pParticle->startingColour_;
	endingColour_			= a_pParticle->endingColour_;
	pos_					= a_v2Pos;
	UG::SetBearingRadians(spriteID_, a_v2Dir.Bearing());
	UG::SetSpritePos(spriteID_, pos_);
	UG::DrawSprite(spriteID_);
}

Particle::~Particle()
{
	UG::DestroySprite(spriteID_);
}

int Particle::Update(const float a_fDeltaTime)
{
	aliveTime_ += a_fDeltaTime;
	if (aliveTime_ <= lifeTime_ && (float)std::div(currentPercentile_, 255).rem == 0)
	{
		pos_ += dir_ * speed_ * a_fDeltaTime;
		currentPercentile_ += a_fDeltaTime / lifeTime_;
		if (currentPercentile_ > 1.0f)
			return 1;
		currentColour_.argb.colours.a = Maths::LinearInterpolate(startingColour_.argb.colours.a, endingColour_.argb.colours.a, currentPercentile_);
		currentColour_.argb.colours.r = Maths::LinearInterpolate(startingColour_.argb.colours.r, endingColour_.argb.colours.r, currentPercentile_);
		currentColour_.argb.colours.g = Maths::LinearInterpolate(startingColour_.argb.colours.g, endingColour_.argb.colours.g, currentPercentile_);
		currentColour_.argb.colours.b = Maths::LinearInterpolate(startingColour_.argb.colours.b, endingColour_.argb.colours.b, currentPercentile_);
		UG::SetSpriteColour(spriteID_, currentColour_);
		UG::SetSpritePos(spriteID_, pos_);
		return 1;
	}
	UG::StopDrawingSprite(spriteID_);

	return 0;
}

UG::SColour Particle::GetStartingColour() const
{
	return startingColour_;
}

UG::SColour Particle::GetEndingColour() const
{
	return endingColour_;
}

Maths::Vector2 Particle::GetSize() const
{
	return size_;
}

Maths::Vector2 Particle::GetDir() const
{
	return dir_;
}

Maths::Vector2 Particle::GetPos() const
{
	return pos_;
}

float Particle::GetLifeTimeSeconds() const
{
	return lifeTime_;
}

float Particle::GetSpeed() const
{
	return speed_;
}

void Particle::StopDrawing()
{
	UG::StopDrawingSprite(spriteID_);
}