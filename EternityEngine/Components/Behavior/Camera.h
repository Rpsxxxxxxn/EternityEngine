#pragma once

#include "../IComponent.h"

namespace Eternity
{
	namespace Component
	{
		enum FrustumPlane
		{
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_UP,
			PLANE_DOWN,
			PLANE_NEAR,
			PLANE_FAR,
			PLANE_MAX,
		};

		class CCamera : public IComponent
		{
		public:
			CCamera(GameObject::IGameObject&);
			~CCamera();
			void Initialize();
			void LateUpdate();
		private:
			void UpdateViewProj();
			void UpdateCalcFrustum();
			void UpdateFps();

			Vector3 m_position;
			Vector3 m_lookat;
			Vector3 m_upward;
			Vector3 m_right;
			Vector3 m_forward;
			Vector3 m_direction;
			Matrix m_view;
			Matrix m_proj;
			Plane m_planes[6];
		};
	}
}