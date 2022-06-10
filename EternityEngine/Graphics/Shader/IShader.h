#pragma once

#include "../../Includer.h"

namespace Eternity
{
	namespace Graphics
	{
		enum ShaderLayout
		{
			POSITION,
			NORMAL,
			TEXCOORD,
			TANGENT,
			BINORMAL,
		};

		struct ConstantBuffer
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
			XMVECTOR camPos;
		};

		class IShader
		{
		public:
			IShader();
			virtual ~IShader() {};
			void Create(string, string);

			// Setter
			void SetWorldMatrix(const Matrix& value);
			void SetViewMatrix(const Matrix& value);
			void SetProjMatrix(const Matrix& value);
			void SetLightViewMatrix(const Matrix& value);
			void SetLightProjMatrix(const Matrix& value);
			void SetEyeVector(const Vector3& value);
			void CommitChanges();
			void SetShader();
		private:
			void CreateShader(string, string);
			void CreateLayout();
			void RasterizerState();
			void SetDepthState();
			void SetConstantBuffer();

			ID3D11VertexShader* m_pVertexShader;
			ID3D11PixelShader* m_pPixelShader;
			ID3D11InputLayout* m_pInputLayout;
			ID3D11RasterizerState* m_pRasterizer;
			ID3D11DepthStencilState* m_pDepthStencil;
			ID3D11Buffer* m_pConstantBuffer;
			ID3DBlob* m_pVsBlob;
			ID3DBlob* m_pPsBlob;

			Matrix m_world;
			Matrix m_view;
			Matrix m_proj;
			Matrix m_lightView;
			Matrix m_lightProj;
			Vector3 m_eyePosition;
		};
	}
}