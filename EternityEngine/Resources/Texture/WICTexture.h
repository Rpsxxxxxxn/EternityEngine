#pragma once

#include "../../Includer.h"

namespace Eternity
{
	namespace Resources
	{
		class CWICTexture
		{
		public:
			CWICTexture();
			~CWICTexture();
			void Create(string path);
			void Release();
			void SetSampler(D3D11_SAMPLER_DESC&);
			void SetSampler(
				D3D11_FILTER,
				D3D11_TEXTURE_ADDRESS_MODE,
				D3D11_COMPARISON_FUNC,
				FLOAT, FLOAT);

			ID3D11Resource* GetResource() const;
			ID3D11ShaderResourceView* GetResourceView() const;
			ID3D11SamplerState* GetSampler() const;
			UINT GetWidth() const;
			UINT GetHeight() const;
		private:
			ID3D11Resource* m_pTexture;
			ID3D11ShaderResourceView* m_pResourceView;
			ID3D11SamplerState* m_pSampler;
			UINT m_width;
			UINT m_height;
		};
	}
}