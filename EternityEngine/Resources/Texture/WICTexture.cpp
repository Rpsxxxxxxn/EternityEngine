#include "WICTexture.h"
#include "../../Graphics/DirectX.h"

namespace Eternity
{
	namespace Resources
	{
		CWICTexture::CWICTexture()
			: m_pTexture(nullptr)
			, m_pResourceView(nullptr)
			, m_pSampler(nullptr)
		{
		}

		CWICTexture::~CWICTexture()
		{
			Release();
		}

		void CWICTexture::Create(string path)
		{
			auto device = Graphics::CDirectX::GetInstance().GetDevice();
			auto filePath = Utility::CHelper::StringToWString(path);
			CreateWICTextureFromFile(device, filePath.c_str(), &m_pTexture, &m_pResourceView);

			if (m_pTexture == nullptr) return;

			ID3D11Texture2D* pTexture = static_cast<ID3D11Texture2D*>(m_pTexture);
			D3D11_TEXTURE2D_DESC desc;
			pTexture->GetDesc(&desc);
			m_width = desc.Width;
			m_height = desc.Height;
			m_height = desc.Height;
		}

		void CWICTexture::Release()
		{
			Utility::SafeRelease(m_pResourceView);
			Utility::SafeRelease(m_pTexture);
			Utility::SafeRelease(m_pSampler);
		}

		void CWICTexture::SetSampler(D3D11_SAMPLER_DESC& desc)
		{
			auto device = Graphics::CDirectX::GetInstance().GetDevice();
			device->CreateSamplerState(&desc, &m_pSampler);
		}

		void CWICTexture::SetSampler(
			D3D11_FILTER filter,
			D3D11_TEXTURE_ADDRESS_MODE address,
			D3D11_COMPARISON_FUNC func,
			FLOAT min,
			FLOAT max)
		{
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = filter;
			samplerDesc.AddressU = address;
			samplerDesc.AddressV = address;
			samplerDesc.AddressW = address;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = func;
			samplerDesc.MinLOD = min;
			samplerDesc.MaxLOD = max;

			auto device = Graphics::CDirectX::GetInstance().GetDevice();
			device->CreateSamplerState(&samplerDesc, &m_pSampler);
		}

		ID3D11Resource* CWICTexture::GetResource() const
		{
			return m_pTexture;
		}

		ID3D11ShaderResourceView* CWICTexture::GetResourceView() const
		{
			return m_pResourceView;
		}

		ID3D11SamplerState* CWICTexture::GetSampler() const
		{
			return m_pSampler;
		}

		UINT CWICTexture::GetWidth() const
		{
			return m_width;
		}

		UINT CWICTexture::GetHeight() const
		{
			return m_height;
		}
	}
}