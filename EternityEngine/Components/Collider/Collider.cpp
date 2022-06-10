#include "Collider.h"

namespace Eternity
{
	namespace Component
	{
		CCollider::CCollider(GameObject::IGameObject& owner)
			: IComponent(owner)
		{
		}

		CCollider::~CCollider()
		{
		}

		void CCollider::Create()
		{
		}
	}
}