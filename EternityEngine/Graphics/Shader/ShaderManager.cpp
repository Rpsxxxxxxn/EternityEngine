#include "ShaderManager.h"

namespace Eternity
{
	namespace Graphics
	{
		CShaderManager::CShaderManager()
		{
		}

		CShaderManager::~CShaderManager()
		{
			for (auto i : m_shaders)
			{
				Utility::SafeDelete(i);
			}
		}

		void CShaderManager::Create()
		{
			AddShader<CNormalShader>();
			AddShader<CDepthBuffer>();
			AddShader<CTerrainShader>();
			AddShader<CSkinMeshShader>();
		}

		void CShaderManager::Update()
		{
			for (auto shader : m_shaders)
			{
				(shader)->SetViewMatrix(m_view);
				(shader)->SetProjMatrix(m_proj);
				(shader)->SetLightViewMatrix(m_lightView);
				(shader)->SetLightProjMatrix(m_lightProj);
				(shader)->SetEyeVector(m_eyePosition);
				(shader)->SetShader();
			}
		}

		void CShaderManager::SetWorldMatrix(const Matrix& value)
		{
			m_world = value;
		}

		void CShaderManager::SetViewMatrix(const Matrix& value)
		{
			m_view = value;
		}

		void CShaderManager::SetProjMatrix(const Matrix& value)
		{
			m_proj = value;
		}

		void CShaderManager::SetLightViewMatrix(const Matrix& value)
		{
			m_lightView = value;
		}

		void CShaderManager::SetLightProjMatrix(const Matrix& value)
		{
			m_lightProj = value;
		}

		void CShaderManager::SetEyeVector(const Vector3& value)
		{
			m_eyePosition = value;
		}
	}
}