#ifndef __SPRITE_H_
#define __SPRITE_H_
#include "Node.h"
class Sprite : public Node
{
	Maths::Vector2 size_;
public:
	Sprite(const char* a_spriteName, const Maths::Vector2& a_v2Size, const Maths::Vector2& a_v2Pos);
	bool IsInsideMe(const Maths::Vector2& a_v2);

	Maths::Vector2 GetSize() { return size_; }
	void SetSize(const Maths::Vector2& a_v2Size) { size_ = a_v2Size; }
};

#endif //__SPRITE_H_