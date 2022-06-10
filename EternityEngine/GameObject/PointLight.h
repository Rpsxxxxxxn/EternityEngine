#pragma once

#include "./IGameObject.h"
#include "./ILightBuffer.h"

namespace Eternity
{
	namespace GameObject
	{
		class PointLight : public IGameObject
		{
			ID3D11Buffer* m_pLightBuffer;
			LightParams m_params;
			Vector3 m_direction;
		public:
			PointLight();
			~PointLight();
			void Initialize();
			void Update();
		};
	}
}