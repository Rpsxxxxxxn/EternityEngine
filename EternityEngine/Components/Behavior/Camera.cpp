#include "Camera.h"
#include "../../Graphics/Shader/ShaderManager.h"

namespace Eternity
{
	namespace Component
	{
		const float VIEW_NEAR = 0.1f;
		const float VIEW_FAR = 10000.0f;

		CCamera::CCamera(GameObject::IGameObject& owner)
			: IComponent(owner)
			, m_position(Vector3::Zero)
			, m_lookat(Vector3::Zero)
			, m_upward(Vector3::Zero)
			, m_right(Vector3::Zero)
			, m_forward(Vector3::Zero)
			, m_direction(Vector3::Zero)
			, m_view(Matrix::Identity)
			, m_proj(Matrix::Identity)
		{
			m_position = Vector3(0.0f, 1.0f, -3.0f);
			m_lookat = Vector3(3.0f, 0.5f, 0.0f);
			m_upward = Vector3(0.0f, 1.0f, 0.0f);
		}

		CCamera::~CCamera()
		{
		}

		void CCamera::Initialize()
		{
			UpdateViewProj();
		}

		void CCamera::LateUpdate()
		{
			UpdateFps();
			UpdateViewProj();
			UpdateCalcFrustum();
		}

		void CCamera::UpdateViewProj()
		{
			m_view = XMMatrixLookAtLH(m_position, m_lookat, m_upward);
			m_proj = XMMatrixPerspectiveFovLH(Utility::Math::ToRadian(60.0f), 16.0f / 9.0f, VIEW_NEAR, VIEW_FAR);

			Graphics::CShaderManager::GetInstance().SetViewMatrix(m_view);
			Graphics::CShaderManager::GetInstance().SetProjMatrix(m_proj);
			Graphics::CShaderManager::GetInstance().SetEyeVector(m_position);
		}

		void CCamera::UpdateCalcFrustum()
		{
			Matrix mVP = XMMatrixMultiply(m_view, m_proj);

			m_planes[PLANE_LEFT].x = mVP._14 + mVP._11;
			m_planes[PLANE_LEFT].y = mVP._24 + mVP._21;
			m_planes[PLANE_LEFT].z = mVP._34 + mVP._31;
			m_planes[PLANE_LEFT].w = mVP._44 + mVP._41;

			m_planes[PLANE_RIGHT].x = mVP._14 - mVP._11;
			m_planes[PLANE_RIGHT].y = mVP._24 - mVP._21;
			m_planes[PLANE_RIGHT].z = mVP._34 - mVP._31;
			m_planes[PLANE_RIGHT].w = mVP._44 - mVP._41;

			m_planes[PLANE_UP].x = mVP._14 - mVP._12;
			m_planes[PLANE_UP].y = mVP._24 - mVP._22;
			m_planes[PLANE_UP].z = mVP._34 - mVP._32;
			m_planes[PLANE_UP].w = mVP._44 - mVP._42;

			m_planes[PLANE_DOWN].x = mVP._14 + mVP._12;
			m_planes[PLANE_DOWN].y = mVP._24 + mVP._22;
			m_planes[PLANE_DOWN].z = mVP._34 + mVP._32;
			m_planes[PLANE_DOWN].w = mVP._44 + mVP._42;

			m_planes[PLANE_NEAR].x = mVP._13;
			m_planes[PLANE_NEAR].y = mVP._23;
			m_planes[PLANE_NEAR].z = mVP._33;
			m_planes[PLANE_NEAR].w = mVP._43;

			m_planes[PLANE_FAR].x = mVP._14 - mVP._13;
			m_planes[PLANE_FAR].y = mVP._24 - mVP._23;
			m_planes[PLANE_FAR].z = mVP._34 - mVP._33;
			m_planes[PLANE_FAR].w = mVP._44 - mVP._43;

			for (int i = 0; i < 6; i++)
				m_planes[i].Normalize();
		}

		void CCamera::UpdateFps()
		{
			auto& mouse = Utility::CMouse::GetInstance();
			auto move = mouse.GetMouseMove();

			auto mouseX = static_cast<float>(move.x);
			auto mouseY = static_cast<float>(move.y);

			if (mouse.IsDown(0))
			{
				m_direction.x += Utility::Math::ToRadian(mouseX) * 0.2f;
				m_direction.y += Utility::Math::ToRadian(mouseY) * 0.2f;
			}

			m_direction.y = Utility::Math::Clamp(m_direction.y, Utility::Math::ToRadian(-45.0f), Utility::Math::ToRadian(75.0f));

			Matrix rotMatrix = XMMatrixRotationRollPitchYaw(m_direction.y, m_direction.x, m_direction.z);

			Vector3 direction = XMVector3TransformCoord(Vector3(0.0f, 0.0f, 1.0f), rotMatrix);
			direction.Normalize();

			auto& input = Utility::CInput::GetInstance();
			if (input.IsDown(DIK_W))
			{
				m_position += direction * 0.1f;
			}

			if (input.IsDown(DIK_S))
			{
				m_position -= direction * 0.1f;
			}

			m_position = m_position;
			m_lookat = m_position + direction;
		}
	}
}