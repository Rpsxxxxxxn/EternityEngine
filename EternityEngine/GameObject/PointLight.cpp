#include "PointLight.h"
#include "../Graphics/DirectX.h"

namespace Eternity
{
	namespace GameObject
	{
		PointLight::PointLight()
			: IGameObject()
			, m_pLightBuffer(nullptr)
			, m_direction(Vector3(0.0f, -1.0f, 1.0f))
		{
			ZeroMemory(&m_params, sizeof(LightParams));
			m_params.ambient = Vector4(1.0f, 0.85f, 0.65f, 1.0f);
			m_params.diffuse = Vector4(1.0f, 0.85f, 0.65f, 1.0f);
			m_params.range = 1.0f;
		}

		PointLight::~PointLight()
		{
			Utility::SafeRelease(m_pLightBuffer);
		}

		void PointLight::Initialize()
		{
			D3D11_BUFFER_DESC bDesc;
			ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));

			bDesc.Usage = D3D11_USAGE_DYNAMIC;
			bDesc.ByteWidth = sizeof(LightBuffer);
			bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;

			auto device_ = Graphics::CDirectX::GetInstance().GetDevice();
			auto hr = device_->CreateBuffer(&bDesc, NULL, &m_pLightBuffer);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "定数バッファの設定に失敗", "Error", MB_OK);
			}
		}

		void PointLight::Update()
		{
			LightBuffer cb;
			ZeroMemory(&cb, sizeof(LightBuffer));
			cb.direction = m_direction;
			cb.ambient = m_params.ambient;
			cb.diffuse = m_params.diffuse;
			cb.range = m_params.range;

			D3D11_MAPPED_SUBRESOURCE mapResrc;
			auto context_ = Graphics::CDirectX::GetInstance().GetContext();
			context_->Map(m_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResrc);
			memcpy_s(mapResrc.pData, mapResrc.RowPitch, (void*)(&cb), sizeof(cb));
			context_->Unmap(m_pLightBuffer, 0);
		}
	}
}