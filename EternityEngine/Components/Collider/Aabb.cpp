#include "Aabb.h"

namespace Eternity
{
	namespace Component
	{
		CAabb::CAabb(GameObject::IGameObject& owner)
			: CCollider(owner)
			, m_center(Vector3::Zero)
			, m_min(Vector3::Zero)
			, m_max(Vector3::Zero)
		{
		}

		CAabb::~CAabb()
		{
		}

		void CAabb::Create()
		{
			CreateVertex();
			CreateBuffer();
		}

		void CAabb::SetMin(const Vector3 value)
		{
			m_min = value;
		}

		void CAabb::SetMax(const Vector3 value)
		{
			m_max = value;
		}

		void CAabb::CreateVertex()
		{
		}

		void CAabb::CreateBuffer()
		{
		}
	}
}