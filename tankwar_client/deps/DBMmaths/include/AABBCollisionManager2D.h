#ifndef __AABB_COLLISION_MANAGER_2D_H_
#define __AABB_COLLISION_MANAGER_2D_H_
#include <vector>
#include "mathLib.h"
namespace Maths
{
	class AABBCollider2D;
	class DLLEXPORT AABBCollisionManager2D
	{
		static AABBCollisionManager2D* s_instance;
		AABBCollisionManager2D();
		~AABBCollisionManager2D();

		std::vector<AABBCollider2D*> colliders_;
		std::vector<AABBCollider2D*> nonStaticColliders_;
	public:
		static AABBCollisionManager2D* instance();

		void UpdatePhysics();

		int Add(AABBCollider2D& a_collider);
		bool Remove(AABBCollider2D& a_collider);

		int Size() const;
		int SizeNonStatic() const;

		AABBCollider2D* ReturnAtIndexStatic(const int a_index);
		AABBCollider2D* ReturnAtIndexNonStatic(const int a_index);

		int FindStatic(const AABBCollider2D& a_AABB);
		int FindNonStatic(const AABBCollider2D& a_AABB);
	};
}
#endif //__AABB_COLLISION_MANAGER_2D_H_