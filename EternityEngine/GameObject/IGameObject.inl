#pragma once

#include "IGameObject.h"

namespace Eternity
{
	namespace GameObject
	{
		template<class _Type>
		inline _Type* IGameObject::AddComponent()
		{
			for (UINT i = 0; i < m_components.size(); i++)
			{
				if (dynamic_cast<_Type*>(m_components[i]) != nullptr)
				{
					return nullptr;
				}
			}

			_Type* type = new _Type(*this);

			Component::IComponent* pComponent
				= static_cast<Component::IComponent*>(type);

			if (pComponent != nullptr)
			{
				m_components.push_back(pComponent);
				return type;
			}

			return nullptr;
		}

		template<class _Type>
		inline _Type* IGameObject::GetComponent()
		{
			for (UINT i = 0; i < m_components.size(); i++)
			{
				_Type* pCom = dynamic_cast<_Type*>(m_components[i]);
				if (pCom != nullptr)
				{
					return pCom;
				}
			}

			return nullptr;
		}
	}
}