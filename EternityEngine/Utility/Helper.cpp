#include "Helper.h"

namespace Eternity
{
	namespace Utility
	{
		// シェーダファイルをコンパイル
		HRESULT CHelper::CompileShaderFromFile(
			LPCWSTR path,
			LPCSTR entry,
			LPCSTR shader,
			ID3DBlob** ppBlob
		)
		{
			HRESULT hr = S_OK;
			ID3DBlob* pErrorBlob = nullptr;

			hr = D3DCompileFromFile(
				path,
				NULL,
				NULL,
				entry,
				shader,
				NULL,
				0,
				ppBlob,
				&pErrorBlob);

			if (FAILED(hr))
				if (pErrorBlob != NULL)
					OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

			SafeRelease(pErrorBlob);
			return hr;
		}

		string CHelper::WStringToString(wstring oWString)
		{
			// wstring → SJIS
			int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
				, -1, (char*)NULL, 0, NULL, NULL);

			// バッファの取得
			CHAR* cpMultiByte = new CHAR[iBufferSize];

			// wstring → SJIS
			WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
				, iBufferSize, NULL, NULL);

			// stringの生成
			std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

			// バッファの破棄
			delete[] cpMultiByte;

			// 変換結果を返す
			return(oRet);
		}

		wstring CHelper::StringToWString(string oString)
		{
			// SJIS → wstring
			int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
				, -1, (wchar_t*)NULL, 0);

			// バッファの取得
			wchar_t* cpUCS2 = new wchar_t[iBufferSize];

			// SJIS → wstring
			MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
				, iBufferSize);

			// stringの生成
			std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

			// バッファの破棄
			delete[] cpUCS2;

			// 変換結果を返す
			return(oRet);
		}

		HRESULT CHelper::CreateVertexShader(
			ID3D11Device* pDevice,
			ID3DBlob* pVsBlob, 
			ID3D11VertexShader** ppVertexShader)
		{
			HRESULT result = S_OK;

			*ppVertexShader = nullptr;

			result = pDevice->CreateVertexShader(
				pVsBlob->GetBufferPointer(),
				pVsBlob->GetBufferSize(),
				nullptr,
				ppVertexShader);

			return result;
		}

		HRESULT CHelper::CreatePixelShader(
			ID3D11Device* pDevice,
			ID3DBlob* pVsBlob, 
			ID3D11PixelShader** ppPixelShader)
		{
			HRESULT result = S_OK;

			*ppPixelShader = nullptr;

			result = pDevice->CreatePixelShader(
				pVsBlob->GetBufferPointer(),
				pVsBlob->GetBufferSize(),
				nullptr,
				ppPixelShader);

			return result;
		}

		HRESULT CHelper::CreateInputLayout(
			ID3D11Device* pDevice,
			D3D11_INPUT_ELEMENT_DESC* pDescs,
			UINT numElements,
			ID3DBlob* pVsBlob,
			ID3D11InputLayout** ppLayout)
		{
			HRESULT result = S_OK;

			*ppLayout = nullptr;

			result = pDevice->CreateInputLayout(
				pDescs,
				numElements,
				pVsBlob->GetBufferPointer(),
				pVsBlob->GetBufferSize(),
				ppLayout);

			return result;
		}

		HRESULT CHelper::CreateVertexBuffer(
			ID3D11Device* pDevice,
			void* pVertexArray, 
			unsigned long vertexSize, 
			ID3D11Buffer** ppVertexBuffer)
		{
			*ppVertexBuffer = nullptr;

			D3D11_BUFFER_DESC vbDesc;
			vbDesc.ByteWidth = vertexSize;
			vbDesc.Usage = D3D11_USAGE_DEFAULT;
			vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbDesc.CPUAccessFlags = 0;
			vbDesc.MiscFlags = 0;
			vbDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA vData;
			vData.pSysMem = pVertexArray;
			vData.SysMemPitch = 0;
			vData.SysMemSlicePitch = 0;

			HRESULT result = S_OK;
			result = pDevice->CreateBuffer(&vbDesc, &vData, ppVertexBuffer);
			return result;
		}

		HRESULT CHelper::CreateIndexBuffer(
			ID3D11Device* pDevice, 
			void* pIndexArray, 
			unsigned long indexSize, 
			ID3D11Buffer** ppIndexBuffer)
		{
			*ppIndexBuffer = nullptr;

			D3D11_BUFFER_DESC ibDesc;
			ibDesc.ByteWidth = indexSize;
			ibDesc.Usage = D3D11_USAGE_DEFAULT;
			ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			ibDesc.CPUAccessFlags = 0;
			ibDesc.MiscFlags = 0;
			ibDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA iData;
			iData.pSysMem = pIndexArray;
			iData.SysMemPitch = 0;
			iData.SysMemSlicePitch = 0;

			HRESULT result = S_OK;
			result = pDevice->CreateBuffer(&ibDesc, &iData, ppIndexBuffer);
			return result;
		}
	}
}