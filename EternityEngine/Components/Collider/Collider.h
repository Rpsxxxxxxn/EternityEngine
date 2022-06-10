#pragma once

#include "../IComponent.h"

namespace Eternity
{
	namespace Component
	{
		enum CollisionType
		{
			FIELD,
			SPHERE,
			AABB,
			OBB,
			RAY,
		};

		class CCollider : public IComponent
		{
		public:
			CCollider(GameObject::IGameObject& owner);
			~CCollider();
			void Create();
		};
	}
}