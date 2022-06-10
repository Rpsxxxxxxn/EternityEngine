#pragma once

#include "Collider.h"

namespace Eternity
{
	namespace Component
	{
		struct DebugVertex
		{

		};

		class CAabb : public CCollider
		{
		public:
			CAabb(GameObject::IGameObject& owner);
			~CAabb();
			void Create();

			void SetMin(const Vector3 value);
			void SetMax(const Vector3 value);
		protected:
			void CreateVertex();
			void CreateBuffer();

			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			Vector3 m_center;
			Vector3 m_min;
			Vector3 m_max;
		};
	}
}