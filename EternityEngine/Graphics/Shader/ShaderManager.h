#pragma once

#include "../../Includer.h"
#include "../../Utility/UtilityBundle.h"
#include "IShader.h"
#include "NormalShader.h"
#include "DepthBuffer.h"
#include "TerrainShader.h"
#include "SkinMeshShader.h"

namespace Eternity
{
	namespace Graphics
	{
		class CShaderManager 
			: public Utility::CSingleton<CShaderManager>
		{
		public:
			CShaderManager();
			~CShaderManager();
			void Create();
			void Update();

			void SetWorldMatrix(const Matrix& value);
			void SetViewMatrix(const Matrix& value);
			void SetProjMatrix(const Matrix& value);
			void SetLightViewMatrix(const Matrix& value);
			void SetLightProjMatrix(const Matrix& value);
			void SetEyeVector(const Vector3& value);

			template<class _Type>
			_Type* AddShader();

			template<class _Type>
			_Type* GetShader();
		private:
			vector<IShader*> m_shaders;

			Matrix m_world;
			Matrix m_view;
			Matrix m_proj;
			Matrix m_lightView;
			Matrix m_lightProj;
			Vector3 m_eyePosition;
		};
	}
}
#include "ShaderManager.inl"