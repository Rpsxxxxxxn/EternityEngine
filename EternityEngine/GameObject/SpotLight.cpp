#include "SpotLight.h"
#include "../Graphics/DirectX.h"

namespace Eternity
{
	namespace GameObject
	{
		SpotLight::SpotLight()
		{
			m_direction = Vector4(0.0f, 0.0f, -1.0f, 1.0f);
			m_ambient = Vector4(1.0f, 0.85f, 0.65f, 1.0f);
			m_diffuse = Vector4(1.0f, 0.85f, 0.65f, 1.0f);
		}

		SpotLight::~SpotLight()
		{
		}

		void SpotLight::Initialize()
		{
		}

		void SpotLight::Update()
		{
		}
	}
}