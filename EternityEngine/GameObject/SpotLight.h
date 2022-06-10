#pragma once

#include "./IGameObject.h"
#include "./ILightBuffer.h"

namespace Eternity
{
	namespace GameObject
	{
		class SpotLight : public IGameObject
		{
			ID3D11Buffer* m_pLightBuffer;
			Vector4 m_direction;
			Vector4 m_ambient;
			Vector4 m_diffuse;
		public:
			SpotLight();
			~SpotLight();
			void Initialize();
			void Update();
		};
	}
}