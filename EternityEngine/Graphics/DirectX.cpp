#include "DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		CDirectX::CDirectX()
		{
		}

		CDirectX::~CDirectX()
		{
			Release();
		}

		void CDirectX::Create(HWND hwnd)
		{
			GetClientRect(hwnd, &m_rect);
			CreateDevice(hwnd);
			CreateSwapchain(hwnd);
			CreateDepth();
			CreateViewport();
		}

		void CDirectX::Release()
		{
			if (m_pDeviceContext) {
				m_pDeviceContext->ClearState();
			}

			Utility::SafeRelease(m_pRenderTargetView);
			Utility::SafeRelease(m_pDepthStencilView);
			Utility::SafeRelease(m_pDepthStencilTexture);
			Utility::SafeRelease(m_pSwapChain);
			Utility::SafeRelease(m_pDeviceContext);
			Utility::SafeRelease(m_pDevice);
		}

		void CDirectX::BeginRender(float r, float g, float b, float a)
		{
			float clearColor[4] = { r, g, b, a };
			m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
			m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}

		void CDirectX::CloseRender()
		{
			m_pSwapChain->Present(1, 0);
		}

		void CDirectX::ResetBackBufferTarget()
		{
			m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
		}

		void CDirectX::ResetViewport()
		{
			m_pDeviceContext->RSSetViewports(1, &m_viewport);
		}

		ID3D11Device* CDirectX::GetDevice() const
		{
			return m_pDevice;
		}

		ID3D11DeviceContext* CDirectX::GetContext() const
		{
			return m_pDeviceContext;
		}

		void CDirectX::CreateDevice(HWND hwnd)
		{
			UINT flags = 0;
			flags |= D3D11_CREATE_DEVICE_DEBUG;

			// DirectX11&ハードウェア対応のみ
			D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

			auto hr = D3D11CreateDevice(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				0,
				NULL,
				0,
				D3D11_SDK_VERSION,
				&m_pDevice,
				NULL,
				&m_pDeviceContext);

			// MSAA用
			for (int i = 1; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i <<= 1)
			{
				UINT Quality;

				if (SUCCEEDED(m_pDevice->CheckMultisampleQualityLevels(
					DXGI_FORMAT_D24_UNORM_S8_UINT,
					i,
					&Quality)))
				{
					if (0 < Quality)
					{
						m_sampleDesc.Count = i;
						m_sampleDesc.Quality = Quality - 1;
					}
				}
			}

		}

		void CDirectX::CreateSwapchain(HWND hwnd)
		{//インターフェース取得
			IDXGIDevice1* dxgi = nullptr;
			if (FAILED(m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi)))
			{
				MessageBox(hwnd, "QueryInterface", "エラー", MB_ICONSTOP);
			}

			//アダプター取得
			IDXGIAdapter* adapter = nullptr;
			if (FAILED(dxgi->GetAdapter(&adapter)))
			{
				MessageBox(hwnd, "GetAdapter", "エラー", MB_ICONSTOP);
			}

			IDXGIFactory* dxgiFactory = nullptr;
			adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
			if (dxgiFactory == nullptr)
			{
				MessageBox(hwnd, "GetParent", "エラー", MB_ICONSTOP);
			}

			DXGI_SWAP_CHAIN_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BufferCount = 1;
			desc.BufferDesc.Width = m_rect.right;
			desc.BufferDesc.Height = m_rect.bottom;
			desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			desc.OutputWindow = hwnd;
			desc.SampleDesc = m_sampleDesc;
			desc.Windowed = true;

			dxgiFactory->CreateSwapChain(m_pDevice, &desc, &m_pSwapChain);
		}

		void CDirectX::CreateDepth()
		{
			ID3D11Texture2D* pBackBuffer;
			auto hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
			Utility::SafeRelease(pBackBuffer);

			D3D11_TEXTURE2D_DESC txDesc;
			ZeroMemory(&txDesc, sizeof(txDesc));
			txDesc.Width = m_rect.right;
			txDesc.Height = m_rect.bottom;
			txDesc.MipLevels = 1;
			txDesc.ArraySize = 1;
			txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			txDesc.SampleDesc = m_sampleDesc;
			txDesc.Usage = D3D11_USAGE_DEFAULT;
			txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			txDesc.CPUAccessFlags = 0;
			txDesc.MiscFlags = 0;
			m_pDevice->CreateTexture2D(&txDesc, nullptr, &m_pDepthStencilTexture);

			// デプスステンシルの設定
			D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
			ZeroMemory(&dsDesc, sizeof(dsDesc));
			dsDesc.Format = txDesc.Format;
			dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			dsDesc.Texture2D.MipSlice = 0;
			m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
		}

		void CDirectX::CreateViewport()
		{
			m_viewport.TopLeftX = 0;
			m_viewport.TopLeftY = 0;
			m_viewport.Width = (float)m_rect.right;
			m_viewport.Height = (float)m_rect.bottom;
			m_viewport.MinDepth = 0.0f;
			m_viewport.MaxDepth = 1.0f;
			m_pDeviceContext->RSSetViewports(1, &m_viewport);
		}
	}
}