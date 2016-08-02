#ifndef __MENU_BUTTON_H_
#define __MENU_BUTTON_H_
namespace Maths
{
	class Matrix4;
	class Vector2;
}
namespace UG
{
	struct SColour;
}
class MenuButton
{
private:
	Maths::Matrix4* m4PosRot_;
	Maths::Vector2* v2Size_;
	int iSpriteID_;
public:
	MenuButton(const char* a_szSpriteName, const Maths::Vector2& a_v2Pos, const Maths::Vector2& a_v2Size, const UG::SColour& a_sColour);
	~MenuButton();
	void StartDrawing();
	void StopDrawing();
	bool ContainsPosition(const Maths::Vector2& a_v2) const;
	void Translate(const Maths::Vector2& a_v2);
	void SetPos(const Maths::Vector2& a_v2);
	Maths::Vector2& GetPos()const;
	void SetColour(const UG::SColour& a_sColour);
};

#endif //__MENU_BUTTON_H_