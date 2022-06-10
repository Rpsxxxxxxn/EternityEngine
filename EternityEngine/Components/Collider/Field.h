#pragma once

#include "Collider.h"

namespace Eternity
{
	namespace Component
	{
		class CField : public CCollider
		{
		public:
			CField(GameObject::IGameObject& owner);
			~CField();
			void Create();
		};
	}
}