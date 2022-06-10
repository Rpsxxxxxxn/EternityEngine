#pragma once

#include "../Includer.h"
#include "../Utility/UtilityBundle.h"
#include "../Components/IComponent.h"
#include "../Components/Transform/Transform.h"
#include "../Provider/GameObjectProvider.h"

namespace Eternity
{
	namespace GameObject
	{
		using namespace Graphics;
		using namespace Provider;

		class IGameObject
		{
			vector<Component::IComponent*> m_components;
		public:
			IGameObject()
			{
				CGameObjectProvider::GetInstance().Register(this);
				AddComponent<Component::Transform>();
			};

			virtual ~IGameObject() {
				for (auto i : m_components)
					Utility::SafeDelete(i);
			};
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Draw() {};

			// Components
			void FirstUpdate()
			{
				for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
					(*itr)->FirstUpdate();
			};
			void LateUpdate()
			{
				for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
					(*itr)->LateUpdate();
			};

			template<class _Type>
			_Type* AddComponent();

			template<class _Type>
			_Type* GetComponent();

			string GetName() const { return m_name; };
			string GetTag() const { return m_tag; };
		protected:
			string m_name;
			string m_tag;
		};
	}
}
#include "IGameObject.inl"