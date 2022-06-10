#include "Transform.h"

namespace Eternity
{
	namespace Component
	{
		// コンストラクタ
		Transform::Transform(GameObject::IGameObject& owner)
			: IComponent(owner)
			, m_position(Vector3::Zero)
			, m_rotation(Vector3::Zero)
			, m_scaling(Vector3::One)
			, m_world(Matrix::Identity)
		{
		}

		// デストラクタ
		Transform::~Transform() {}

		// 初期化
		void Transform::Initialize()
		{
			m_position = Vector3::Zero;
			m_rotation = Vector3::Zero;
			m_scaling = Vector3::Zero;
			m_world = Matrix::Identity;
		}

		// 遅延更新
		void Transform::LateUpdate()
		{
			m_world = Matrix::CreateScale(m_scaling.x, m_scaling.y, m_scaling.z);
			m_world *= Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z);
			m_world *= Matrix::CreateTranslation(m_position);
		}

		// 位置の設定
		void Transform::SetPosition(const Vector3& value)
		{
			m_position = value;
		}

		// 回転の設定
		void Transform::SetRotation(const Vector3& value)
		{
			m_rotation = value;
		}

		// 拡大の設定
		void Transform::SetScaling(const Vector3& value)
		{
			m_scaling = value;
		}

		// 行列の設定
		void Transform::SetTransform(const Matrix& value)
		{
			m_world = value;
		}

		// 位置の取得
		Vector3 Transform::GetPosition() const
		{
			return m_position;
		}

		// 回転の取得
		Vector3 Transform::GetRotation() const
		{
			return m_rotation;
		}

		// 拡大の取得
		Vector3 Transform::GetScaling() const
		{
			return m_scaling;
		}

		// 世界行列の取得
		Matrix Transform::GetTransform() const
		{
			return m_world;
		}
	}
}