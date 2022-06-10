#include "IShader.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		// �R���X�g���N�^
		IShader::IShader()
		{
			m_world			= Matrix::Identity;
			m_view			= Matrix::Identity;
			m_proj			= Matrix::Identity;
			m_eyePosition	= Vector3::Zero;
		}

		// ��������
		void IShader::Create(
			string _vsPath,
			string _psPath
		)
		{
			CreateShader(_vsPath, _psPath);
			CreateLayout();
			RasterizerState();
			SetDepthState();
			SetConstantBuffer();
		}

		// ���E�s��̐ݒ�
		void IShader::SetWorldMatrix(const Matrix& value)
		{
			m_world = value;
		}

		// �r���[�s��̐ݒ�
		void IShader::SetViewMatrix(const Matrix& value)
		{
			m_view = value;
		}

		// ���e�s��̐ݒ�
		void IShader::SetProjMatrix(const Matrix& value)
		{
			m_proj = value;
		}

		void IShader::SetLightViewMatrix(const Matrix& value)
		{
			m_lightView = value;
		}

		void IShader::SetLightProjMatrix(const Matrix& value)
		{
			m_lightProj = value;
		}
 
		void IShader::SetEyeVector(const Vector3& value)
		{
			m_eyePosition = value;
		}

		// �V�F�[�_�փ��\�[�X��L��
		void IShader::CommitChanges()
		{
			ConstantBuffer cb;
			ZeroMemory(&cb, sizeof(ConstantBuffer));
			cb.world	= m_world;
			cb.view		= m_view;
			cb.proj		= m_proj;
			cb.camPos	= m_eyePosition;

			cb.world	= XMMatrixTranspose(cb.world);
			cb.view		= XMMatrixTranspose(cb.view);
			cb.proj		= XMMatrixTranspose(cb.proj);

			D3D11_MAPPED_SUBRESOURCE mapResrc;
			auto context_ = CDirectX::GetInstance().GetContext();
			context_->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResrc);
			memcpy_s(mapResrc.pData, mapResrc.RowPitch, (void*)(&cb), sizeof(cb));
			context_->Unmap(m_pConstantBuffer, 0);
		}

		void IShader::SetShader()
		{
			auto context_ = CDirectX::GetInstance().GetContext();
			context_->VSSetShader(m_pVertexShader, nullptr, 0);
			context_->PSSetShader(m_pPixelShader, nullptr, 0);
			context_->IASetInputLayout(m_pInputLayout);
			context_->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
			context_->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		}

		// �V�F�[�_�̐���
		void IShader::CreateShader(
			string vsPath,
			string psPath
		)
		{
			auto vs = Utility::CHelper::StringToWString(vsPath);
			auto hr = Utility::CHelper::CompileShaderFromFile(
				vs.c_str(),
				"main",
				"vs_5_0",
				&m_pVsBlob);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "���_�V�F�[�_�̐����Ɏ��s", "", MB_OK);
				return;
			}

			auto ps = Utility::CHelper::StringToWString(psPath);
			hr = Utility::CHelper::CompileShaderFromFile(
				ps.c_str(),
				"main",
				"ps_5_0",
				&m_pPsBlob);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "�s�N�Z���V�F�[�_�̐����Ɏ��s", "", MB_OK);
				return;
			}

			auto device = CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateVertexShader(device, m_pVsBlob, &m_pVertexShader);
			Utility::CHelper::CreatePixelShader(device, m_pPsBlob, &m_pPixelShader);
		}

		// ���C�A�E�g�̐ݒ�
		void IShader::CreateLayout()
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{"POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"BLENDWEIGHT",  0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			UINT numElement = ARRAYSIZE(layout);

			auto device = CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateInputLayout(device, layout, numElement, m_pVsBlob, &m_pInputLayout);

			Utility::SafeRelease(m_pVsBlob);
		}

		// ���X�^���C�Y�ݒ�
		void IShader::RasterizerState()
		{
			D3D11_RASTERIZER_DESC rsDesc;
			ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));

			// ���X�^���C�Y�ݒ�
			rsDesc.FillMode = D3D11_FILL_SOLID;
			rsDesc.CullMode = D3D11_CULL_BACK;
			rsDesc.DepthClipEnable = true;

			// �f�o�C�X�ɐݒ�
			auto device = CDirectX::GetInstance().GetDevice();
			auto hr = device->CreateRasterizerState(&rsDesc, &m_pRasterizer);

			// �����_�����O�R���e�L�X�g�ɐݒ�
			auto context = CDirectX::GetInstance().GetContext();
			context->RSSetState(m_pRasterizer);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "���X�^���C�U�ݒ�Ɏ��s", "Error", MB_OK);
			}
		}

		// �f�v�X�X�e���V���ݒ�
		void IShader::SetDepthState()
		{
			D3D11_DEPTH_STENCIL_DESC dsDesc;
			ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			
			dsDesc.DepthEnable = true;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
			dsDesc.StencilEnable = false;

			auto device = CDirectX::GetInstance().GetDevice();
			auto hr = device->CreateDepthStencilState(&dsDesc, &m_pDepthStencil);

			auto context = Graphics::CDirectX::GetInstance().GetContext();
			context->OMSetDepthStencilState(m_pDepthStencil, 0);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "�f�v�X�X�e���V���ݒ�Ɏ��s", "Error", MB_OK);
			}
		}

		// �萔�o�b�t�@�̐ݒ�
		void IShader::SetConstantBuffer()
		{
			D3D11_BUFFER_DESC bDesc;
			ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));

			bDesc.ByteWidth = sizeof(ConstantBuffer);
			bDesc.Usage = D3D11_USAGE_DYNAMIC;
			bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bDesc.MiscFlags = 0;
			bDesc.StructureByteStride = 0;

			auto device = CDirectX::GetInstance().GetDevice();
			auto hr = device->CreateBuffer(&bDesc, NULL, &m_pConstantBuffer);

			if (FAILED(hr))
			{
				MessageBox(nullptr, "�萔�o�b�t�@�̐ݒ�Ɏ��s", "Error", MB_OK);
			}
		}
	}
}