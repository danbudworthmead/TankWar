#ifndef __WALL_COLLIDER_2D_H_
#define __WALL_COLLIDER_2D_H_
#include "mathLib.h"

namespace Maths
{
	class Vector2;
	class DLLEXPORT WallCollider2D
	{
		Vector2 *start_, *end_, *normal_;
		bool isEnabled_;
	public:
		WallCollider2D();
		WallCollider2D(const Maths::Vector2& a_start, const Maths::Vector2& a_end, const bool a_isEnabled = true);
		~WallCollider2D();

		void UpdateNormal();
		Vector2 GetNormal() const;

		Vector2 GetStart() const;
		Vector2 GetEnd() const;

		friend float DistanceToWall(const WallCollider2D& wall, const Vector2& v2);
	};
}
#endif //__WALL_COLLIDER_2D_H_