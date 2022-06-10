#pragma once

#include "../Includer.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Graphics
	{
		class CDirectX : public Utility::CSingleton<CDirectX>
		{
		public:
			CDirectX();
			~CDirectX();
			void Create(HWND hwnd);
			void Release();
			void BeginRender(float r, float g, float b, float a);
			void CloseRender();
			void ResetBackBufferTarget();
			void ResetViewport();

			ID3D11Device* GetDevice() const;
			ID3D11DeviceContext* GetContext() const;
		private:
			void CreateDevice(HWND hwnd);
			void CreateSwapchain(HWND hwnd);
			void CreateDepth();
			void CreateViewport();

			D3D11_VIEWPORT m_viewport;
			ID3D11Device* m_pDevice;
			ID3D11DeviceContext* m_pDeviceContext;
			IDXGISwapChain* m_pSwapChain;
			ID3D11Texture2D* m_pDepthStencilTexture;
			ID3D11RenderTargetView* m_pRenderTargetView;
			ID3D11DepthStencilView* m_pDepthStencilView;
			DXGI_SAMPLE_DESC m_sampleDesc;
			RECT m_rect;
		};
	}
}