#pragma once

#include "../Includer.h"
#include "Memory.h"

namespace Eternity
{
	namespace Utility
	{
		class CHelper
		{
		public:
			static HRESULT CompileShaderFromFile(LPCWSTR path, LPCSTR entry, LPCSTR shader, ID3DBlob** ppBlob);

			static string WStringToString(wstring oWString);
			static wstring StringToWString(string oString);

			static HRESULT CreateVertexShader(ID3D11Device* pDevice, ID3DBlob* pVsBlob, ID3D11VertexShader** ppVertexShader);
			static HRESULT CreatePixelShader(ID3D11Device* pDevice, ID3DBlob* pVsBlob, ID3D11PixelShader** ppPixelShader);
			static HRESULT CreateInputLayout(ID3D11Device* pDevice, D3D11_INPUT_ELEMENT_DESC* pDescs, UINT numElements, ID3DBlob* pVsBlob, ID3D11InputLayout** ppLayout);
		
			static HRESULT CreateVertexBuffer(ID3D11Device* pDevice, void* pVertexArray, unsigned long vertexSize, ID3D11Buffer** ppVertexBuffer);
			static HRESULT CreateIndexBuffer(ID3D11Device* pDevice, void* pIndexArray, unsigned long indexSize, ID3D11Buffer** ppIndexBuffer);
		};
	}
}