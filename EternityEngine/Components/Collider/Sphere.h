#pragma once

#include "Collider.h"

namespace Eternity
{
	namespace Component
	{
		class CSphere : public CCollider
		{
		public:
			CSphere(GameObject::IGameObject& owner);
			~CSphere();
			void Create();
		};
	}
}