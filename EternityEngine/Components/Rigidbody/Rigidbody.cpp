#include "Rigidbody.h"
#include "../Transform/Transform.h"
#include "../../GameObject/IGameObject.h"

namespace Eternity
{
	namespace Component
	{
		const float GRAVITY = -9.8f;

		// �R���X�g���N�^
		Rigidbody::Rigidbody(GameObject::IGameObject& owner)
			: IComponent(owner)
			, m_mass(0.0f)
			, m_bound(0.0f)
			, m_force(0.0f)
			, m_velocity(Vector3::Zero)
			, m_isUseGravity(true)
			, m_isKinematics(false)
		{
		}

		// �f�X�g���N�^
		Rigidbody::~Rigidbody()
		{
		}

		// ����������
		void Rigidbody::Initialize()
		{
		}

		// �x���X�V����
		void Rigidbody::LateUpdate()
		{
			float massGravity = 0.0f;
			float acceleration = 0.0f;

			// �d�͌v�Z
			if (m_isUseGravity)
			{
				massGravity = m_mass * GRAVITY;
				acceleration = massGravity / m_mass;
			}

			// �������Z�e��
			if (m_isKinematics)
			{
				auto trans = m_owner.GetComponent<Transform>();
				if (trans == nullptr)
				{
					MessageBox(nullptr, "Transform���Ȃ��ŁH", "�G���[", MB_OK);
					return;
				}

				// TODO: �����ƕύX������ŁH
				auto position = trans->GetPosition();

				m_velocity.y += acceleration * Utility::CTimer::DeltaTime;
				position.y += m_velocity.y * Utility::CTimer::DeltaTime;

				trans->SetPosition(position);
			}
		}

		// �͂�������
		void Rigidbody::AddForce(const float value)
		{
			m_force = value;
		}

		// ���ʂ̐ݒ�
		void Rigidbody::SetMass(const float value)
		{
			m_mass = value;
		}

		// �o�E���h�̐ݒ�
		void Rigidbody::SetBound(const float value)
		{
			m_bound = value;
		}

		// �d�͂�L���ɂ��邩�̐ݒ�
		void Rigidbody::SetUseGravity(const bool value)
		{
			m_isUseGravity = value;
		}

		// ���Z������K�����邩�H
		void Rigidbody::SetKinematics(const bool value)
		{
			m_isKinematics = value;
		}

		float Rigidbody::GetMass() const
		{
			return m_mass;
		}

		float Rigidbody::GetBound() const
		{
			return m_bound;
		}

		bool Rigidbody::GetUseGravity() const
		{
			return m_isUseGravity;
		}

		bool Rigidbody::GetKinematics() const
		{
			return m_isKinematics;
		}
	}
}