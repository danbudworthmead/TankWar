#include "MenuButton.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "UGFW++.h"
MenuButton::MenuButton(const char* a_szSpriteName, const Maths::Vector2& a_v2Pos, const Maths::Vector2& a_v2Size, const UG::SColour& a_sColour)
{
	m4PosRot_ = new Maths::Matrix4();
	v2Size_ = new Maths::Vector2(a_v2Size);
	iSpriteID_ = UG::CreateSprite(a_szSpriteName, a_v2Size.x, a_v2Size.y, true, a_sColour);
	UG::MoveSprite(iSpriteID_, a_v2Pos.xy);
	UG::GetSpriteMatrix(iSpriteID_, m4PosRot_->values_);
}
MenuButton::~MenuButton()
{
	delete v2Size_;
	delete m4PosRot_;
}
void MenuButton::StartDrawing()
{
	UG::DrawSprite(iSpriteID_);
}
void MenuButton::StopDrawing()
{
	UG::StopDrawingSprite(iSpriteID_);
}
bool MenuButton::ContainsPosition(const Maths::Vector2& a_v2) const
{
	Maths::Vector2 halfsize = Maths::Vector2(v2Size_->x * 0.5f, v2Size_->y * 0.5f);
	if (a_v2.x > m4PosRot_->GetT().x + halfsize.x)
		return false;
	if (a_v2.x < m4PosRot_->GetT().x - halfsize.x)
		return false;
	if (a_v2.y > m4PosRot_->GetT().y + halfsize.y)
		return false;
	if (a_v2.y < m4PosRot_->GetT().y - halfsize.y)
		return false;
	return true;
}
void MenuButton::Translate(const Maths::Vector2& a_v2)
{
	m4PosRot_->Translate(Maths::Vector2(a_v2));
}
void MenuButton::SetPos(const Maths::Vector2& a_v2)
{
	m4PosRot_->SetT(Maths::Vector4(a_v2.x, a_v2.y, 0, 0));
}
Maths::Vector2& MenuButton::GetPos()const
{
	Maths::Vector4 v4 = m4PosRot_->GetT();
	return Maths::Vector2(v4.x, v4.y);
}
void MenuButton::SetColour(const UG::SColour& a_sColour)
{
	UG::SetSpriteColour(iSpriteID_, a_sColour);
}