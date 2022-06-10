#include "RenderTexture.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		// コンストラクタ
		CRenderTexture::CRenderTexture()
			: m_pRenderTargetTexture(nullptr)
			, m_pDepthStencilBuffer(nullptr)
			, m_pRenderTargetView(nullptr)
			, m_pShaderResourceView(nullptr)
			, m_pDepthStencilView(nullptr)
		{
		}

		// デストラクタ
		CRenderTexture::~CRenderTexture()
		{
			Utility::SafeRelease(m_pRenderTargetTexture);
			Utility::SafeRelease(m_pDepthStencilBuffer);
			Utility::SafeRelease(m_pRenderTargetView);
			Utility::SafeRelease(m_pShaderResourceView);
			Utility::SafeRelease(m_pDepthStencilView);
		}

		// 生成処理
		void CRenderTexture::Create(
			int width,
			int height)
		{
			auto device_ = Graphics::CDirectX::GetInstance().GetDevice();

			// シャドウマップ用テクスチャ生成処理
			D3D11_TEXTURE2D_DESC texDesc;
			ZeroMemory(&texDesc, sizeof(texDesc));
			texDesc.Width = width;
			texDesc.Height = height;
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			texDesc.SampleDesc.Count = 1;
			texDesc.Usage = D3D11_USAGE_DEFAULT;
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			texDesc.CPUAccessFlags = 0;
			texDesc.MiscFlags = 0;

			device_->CreateTexture2D(&texDesc, nullptr, &m_pRenderTargetTexture);

			// レンダリングターゲットビューの設定＆生成処理
			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = texDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			device_->CreateRenderTargetView(m_pRenderTargetTexture, &renderTargetViewDesc, &m_pRenderTargetView);

			// シェーダリソースビューの設定＆生成処理
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResrcViewDesc;
			shaderResrcViewDesc.Format = texDesc.Format;
			shaderResrcViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResrcViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResrcViewDesc.Texture2D.MipLevels = 1;

			device_->CreateShaderResourceView(m_pRenderTargetTexture, &shaderResrcViewDesc, &m_pShaderResourceView);

			// 深度バッファの設定＆生成処理
			D3D11_TEXTURE2D_DESC depthBufferDesc;
			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
			depthBufferDesc.Width = width;
			depthBufferDesc.Height = height;
			depthBufferDesc.MipLevels = 1;
			depthBufferDesc.ArraySize = 1;
			depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags = 0;
			depthBufferDesc.MiscFlags = 0;

			device_->CreateTexture2D(&depthBufferDesc, nullptr, &m_pDepthStencilBuffer);

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			device_->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);

			// ビューポートの設定
			m_viewport.Width = (float)width;
			m_viewport.Height = (float)height;
			m_viewport.MinDepth = 0.0f;
			m_viewport.MaxDepth = 1.0f;
			m_viewport.TopLeftX = 0.0f;
			m_viewport.TopLeftY = 0.0f;

			D3D11_SAMPLER_DESC samplerDesc;
			ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

			samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
			samplerDesc.BorderColor[0] = 1.0f;
			samplerDesc.BorderColor[1] = 1.0f;
			samplerDesc.BorderColor[2] = 1.0f;
			samplerDesc.BorderColor[3] = 1.0f;
			samplerDesc.MinLOD = -FLT_MAX;
			samplerDesc.MaxLOD = +FLT_MAX;

			device_->CreateSamplerState(&samplerDesc, &m_pSamplerState);
		}

		// レンダリングビューと深度ビューのバッファをサラにする
		void CRenderTexture::ClearRenderTarget()
		{
			auto context_ = Graphics::CDirectX::GetInstance().GetContext();

			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			context_->ClearRenderTargetView(m_pRenderTargetView, clearColor);
			context_->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}

		// レンダリングターゲットの設定を行う
		void CRenderTexture::SetRenderTarget()
		{
			auto context_ = Graphics::CDirectX::GetInstance().GetContext();

			context_->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
			context_->RSSetViewports(1, &m_viewport);
			context_->PSSetSamplers(1, 1, &m_pSamplerState);
		}

		void CRenderTexture::SetRenderResourceView()
		{
			auto context_ = Graphics::CDirectX::GetInstance().GetContext();
			context_->PSSetShaderResources(1, 1, &m_pShaderResourceView);
		}

		ID3D11ShaderResourceView* CRenderTexture::GetResourceView()
		{
			return m_pShaderResourceView;
		}
	}
}