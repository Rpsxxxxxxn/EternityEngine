#pragma once

// インクルード
#include "ShaderManager.h"

namespace Eternity
{
	namespace Graphics
	{
		template<class _Type>
		inline _Type* CShaderManager::AddShader()
		{
			for (UINT i = 0; i < m_shaders.size(); i++)
			{
				if (dynamic_cast<_Type*>(m_shaders[i]) != nullptr)
				{
					return nullptr;
				}
			}

			_Type* type = new _Type();

			IShader* pShader = static_cast<IShader*>(type);

			if (pShader != nullptr)
			{
				m_shaders.push_back(pShader);
				return type;
			}

			return nullptr;
		}

		// シェーダの取得
		template<class _Type>
		inline _Type* CShaderManager::GetShader()
		{
			for (UINT i = 0; i < m_shaders.size(); i++)
			{
				_Type* pShader = dynamic_cast<_Type*>(m_shaders[i]);
				if (pShader != nullptr)
				{
					return pShader;
				}
			}

			return nullptr;
		}
	}
}