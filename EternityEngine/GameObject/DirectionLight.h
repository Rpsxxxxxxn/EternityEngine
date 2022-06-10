#pragma once

#include "./IGameObject.h"
#include "./ILightBuffer.h"

namespace Eternity
{
	namespace GameObject
	{
		class CDirectionLight : public IGameObject
		{
			ID3D11Buffer* m_pLightBuffer;
			LightParams m_params;
			Vector3 m_position;
			Vector3 m_direction;
			Vector3 m_lookat;
			Vector3 m_upward;
		public:
			CDirectionLight();
			~CDirectionLight();
			void Initialize() override;
			void Update() override;
			void Draw() override {};
		private:
			void CreateBuffer();
			void UpdateVP();
			void UpdateDirection();
			void SetConstant();
			void SetShader();
		};
	}
}