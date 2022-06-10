#include "Transform.h"

namespace Eternity
{
	namespace Component
	{
		// �R���X�g���N�^
		Transform::Transform(GameObject::IGameObject& owner)
			: IComponent(owner)
			, m_position(Vector3::Zero)
			, m_rotation(Vector3::Zero)
			, m_scaling(Vector3::One)
			, m_world(Matrix::Identity)
		{
		}

		// �f�X�g���N�^
		Transform::~Transform() {}

		// ������
		void Transform::Initialize()
		{
			m_position = Vector3::Zero;
			m_rotation = Vector3::Zero;
			m_scaling = Vector3::Zero;
			m_world = Matrix::Identity;
		}

		// �x���X�V
		void Transform::LateUpdate()
		{
			m_world = Matrix::CreateScale(m_scaling.x, m_scaling.y, m_scaling.z);
			m_world *= Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z);
			m_world *= Matrix::CreateTranslation(m_position);
		}

		// �ʒu�̐ݒ�
		void Transform::SetPosition(const Vector3& value)
		{
			m_position = value;
		}

		// ��]�̐ݒ�
		void Transform::SetRotation(const Vector3& value)
		{
			m_rotation = value;
		}

		// �g��̐ݒ�
		void Transform::SetScaling(const Vector3& value)
		{
			m_scaling = value;
		}

		// �s��̐ݒ�
		void Transform::SetTransform(const Matrix& value)
		{
			m_world = value;
		}

		// �ʒu�̎擾
		Vector3 Transform::GetPosition() const
		{
			return m_position;
		}

		// ��]�̎擾
		Vector3 Transform::GetRotation() const
		{
			return m_rotation;
		}

		// �g��̎擾
		Vector3 Transform::GetScaling() const
		{
			return m_scaling;
		}

		// ���E�s��̎擾
		Matrix Transform::GetTransform() const
		{
			return m_world;
		}
	}
}