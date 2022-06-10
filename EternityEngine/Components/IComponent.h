#pragma once

// インクルード
#include "../Includer.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace GameObject
	{
		class IGameObject;
	}

	namespace Component
	{
		class IComponent
		{
		public:
			IComponent(GameObject::IGameObject& owner) : m_owner(owner) {};
			virtual ~IComponent() {};
			virtual void Initialize() = 0;
			virtual void FirstUpdate() {};
			virtual void LateUpdate() {};

			GameObject::IGameObject* GetGameObject() { return &m_owner; };
		protected:
			GameObject::IGameObject& m_owner;
		};
	}
}