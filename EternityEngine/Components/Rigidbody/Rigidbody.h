#pragma once

#include "../IComponent.h"

namespace Eternity
{
	namespace Component
	{
		class Rigidbody : public IComponent
		{
		public:
			Rigidbody(GameObject::IGameObject&);
			~Rigidbody();
			void Initialize();
			void LateUpdate();

			// Setter
			void AddForce(const float);
			void SetMass(const float);
			void SetBound(const float);
			void SetUseGravity(const bool);
			void SetKinematics(const bool);

			// Getter
			float GetMass() const;
			float GetBound() const;
			bool GetUseGravity() const;
			bool GetKinematics() const;
		private:
			float m_mass;
			float m_bound;
			float m_force;
			Vector3 m_velocity;
			bool m_isUseGravity;
			bool m_isKinematics;
		};
	}
}