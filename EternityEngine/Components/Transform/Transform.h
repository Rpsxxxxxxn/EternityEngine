#pragma once

#include "../IComponent.h"

namespace Eternity
{
	namespace Component
	{
		class Transform : public IComponent
		{
		public:
			Transform(GameObject::IGameObject&);
			~Transform();
			void Initialize();
			void LateUpdate();

			// Setter
			void SetPosition(const Vector3&);
			void SetRotation(const Vector3&);
			void SetScaling(const Vector3&);
			void SetTransform(const Matrix&);

			// Getter
			Vector3 GetPosition() const;
			Vector3 GetRotation() const;
			Vector3 GetScaling() const;
			Matrix GetTransform() const;
		private:
			Matrix m_world;
			Vector3 m_position;
			Vector3 m_rotation;
			Vector3 m_scaling;
		};
	}
}