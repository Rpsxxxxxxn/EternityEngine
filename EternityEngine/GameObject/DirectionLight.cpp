#include "DirectionLight.h"
#include "../Graphics/DirectX.h"

namespace Eternity
{
	namespace GameObject
	{
		// コンストラクタ
		CDirectionLight::CDirectionLight()
			: IGameObject()
			, m_pLightBuffer(nullptr)
			, m_position(Vector3(-20.0f, 20.0f, -20.0f))
			, m_direction(Vector3(0.5f, 0.5f, -0.2f))
			, m_lookat(Vector3(0.1f, 0.1f, 0.1f))
			, m_upward(Vector3(0.0f, 1.0f, 0.0f))
		{
			ZeroMemory(&m_params, sizeof(LightParams));
			m_params.ambient = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
			m_params.diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
			m_params.lightView = Matrix::Identity;
			m_params.lightProj = Matrix::Identity;

			m_name = "DirectionLight";

			auto transform = GetComponent<Component::Transform>();
			transform->SetPosition(m_position);
			transform->SetRotation(m_direction);
		}

		// デストラクタ
		CDirectionLight::~CDirectionLight()
		{
			Utility::SafeRelease(m_pLightBuffer);
		}

		// 初期化処理
		void CDirectionLight::Initialize()
		{
			CreateBuffer();
			UpdateVP();
		}

		// 更新処理
		void CDirectionLight::Update()
		{
			UpdateVP();
			UpdateDirection();
			SetConstant();
			SetShader();
		}

		// ライト用定数バッファの生成
		void CDirectionLight::CreateBuffer()
		{
			D3D11_BUFFER_DESC bDesc;
			ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));
			bDesc.Usage = D3D11_USAGE_DYNAMIC;
			bDesc.ByteWidth = sizeof(LightBuffer);
			bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;

			auto device = Graphics::CDirectX::GetInstance().GetDevice();
			auto hr = device->CreateBuffer(&bDesc, NULL, &m_pLightBuffer);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "定数バッファの設定に失敗", "エラー", MB_OK);
			}
		}

		// 方向の計算
		void CDirectionLight::UpdateDirection()
		{
			Matrix rotMatrix = XMMatrixRotationRollPitchYaw(
				m_direction.y,
				m_direction.x,
				m_direction.z);

			Vector3 direction = XMVector3TransformCoord(Vector3(0.0f, 0.0f, 1.0f), rotMatrix);
			direction.Normalize();

			m_position = m_position;
			m_lookat = m_position + direction;

			auto transform = GetComponent<Component::Transform>();
			transform->SetPosition(m_position);
			transform->SetRotation(m_direction);
		}

		// ViewProjの更新
		void CDirectionLight::UpdateVP()
		{
			auto transform = GetComponent<Component::Transform>();
			m_position = transform->GetPosition();
			m_direction = transform->GetRotation();

			m_params.lightView = XMMatrixLookAtLH(m_position, m_lookat, m_upward);
			m_params.lightProj = XMMatrixOrthographicLH(100.0f, 100.0f, 0.1f, 500.0f);
		}

		// 定数に設定する
		void CDirectionLight::SetConstant()
		{
			LightBuffer cb;
			ZeroMemory(&cb, sizeof(cb));
			cb.position		= m_position;
			cb.direction	= m_direction;
			cb.ambient		= m_params.ambient;
			cb.diffuse		= m_params.diffuse;
			cb.lightView	= m_params.lightView;
			cb.lightProj	= m_params.lightProj;
			cb.lightView	= XMMatrixTranspose(cb.lightView);
			cb.lightProj	= XMMatrixTranspose(cb.lightProj);

			D3D11_MAPPED_SUBRESOURCE mapResrc;
			auto pContext = Graphics::CDirectX::GetInstance().GetContext();

			pContext->Map(m_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResrc);
			memcpy_s(mapResrc.pData, mapResrc.RowPitch, (void*)(&cb), sizeof(cb));
			pContext->Unmap(m_pLightBuffer, 0);
		}

		// シェーダの設定
		void CDirectionLight::SetShader()
		{
			CShaderManager::GetInstance().SetLightViewMatrix(m_params.lightView);
			CShaderManager::GetInstance().SetLightProjMatrix(m_params.lightProj);

			auto context_ = Graphics::CDirectX::GetInstance().GetContext();
			context_->VSSetConstantBuffers(1, 1, &m_pLightBuffer);
			context_->PSSetConstantBuffers(1, 1, &m_pLightBuffer);
		}
	}
}