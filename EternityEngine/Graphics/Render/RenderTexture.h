#pragma once

#include "../../Includer.h"
#include "../../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Graphics
	{
		class CRenderTexture
		{
		public:
			CRenderTexture();
			~CRenderTexture();
			void Create(int, int);
			void ClearRenderTarget();
			void SetRenderTarget();
			void SetRenderResourceView();

			ID3D11ShaderResourceView* GetResourceView();
		private:
			ID3D11SamplerState* m_pSamplerState;
			ID3D11Texture2D* m_pRenderTargetTexture;
			ID3D11Texture2D* m_pDepthStencilBuffer;
			ID3D11RenderTargetView* m_pRenderTargetView;
			ID3D11ShaderResourceView* m_pShaderResourceView;
			ID3D11DepthStencilView* m_pDepthStencilView;
			D3D11_VIEWPORT m_viewport;
		};
	}
}