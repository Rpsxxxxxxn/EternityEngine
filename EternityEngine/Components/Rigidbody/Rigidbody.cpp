#include "Rigidbody.h"
#include "../Transform/Transform.h"
#include "../../GameObject/IGameObject.h"

namespace Eternity
{
	namespace Component
	{
		const float GRAVITY = -9.8f;

		// コンストラクタ
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

		// デストラクタ
		Rigidbody::~Rigidbody()
		{
		}

		// 初期化処理
		void Rigidbody::Initialize()
		{
		}

		// 遅延更新処理
		void Rigidbody::LateUpdate()
		{
			float massGravity = 0.0f;
			float acceleration = 0.0f;

			// 重力計算
			if (m_isUseGravity)
			{
				massGravity = m_mass * GRAVITY;
				acceleration = massGravity / m_mass;
			}

			// 物理演算影響
			if (m_isKinematics)
			{
				auto trans = m_owner.GetComponent<Transform>();
				if (trans == nullptr)
				{
					MessageBox(nullptr, "Transformがないで？", "エラー", MB_OK);
					return;
				}

				// TODO: ちゃんと変更するんやで？
				auto position = trans->GetPosition();

				m_velocity.y += acceleration * Utility::CTimer::DeltaTime;
				position.y += m_velocity.y * Utility::CTimer::DeltaTime;

				trans->SetPosition(position);
			}
		}

		// 力を加える
		void Rigidbody::AddForce(const float value)
		{
			m_force = value;
		}

		// 質量の設定
		void Rigidbody::SetMass(const float value)
		{
			m_mass = value;
		}

		// バウンドの設定
		void Rigidbody::SetBound(const float value)
		{
			m_bound = value;
		}

		// 重力を有効にするかの設定
		void Rigidbody::SetUseGravity(const bool value)
		{
			m_isUseGravity = value;
		}

		// 演算処理を適応するか？
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