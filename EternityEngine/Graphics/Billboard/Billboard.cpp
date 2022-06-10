#include "Billboard.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		CBillboard::CBillboard()
			: m_pVertexBuffer(nullptr)
			, m_vertexCount(4)
		{
		}

		CBillboard::~CBillboard()
		{
			Utility::SafeRelease(m_pVertexBuffer);
		}

		void CBillboard::Create()
		{
			BillboardVertex* pVertices = new BillboardVertex[m_vertexCount];

			pVertices[0].position = Vector3( 1.0f, -1.0f, 0.0f);
			pVertices[1].position = Vector3( 1.0f,  1.0f, 0.0f);
			pVertices[2].position = Vector3(-1.0f, -1.0f, 0.0f);
			pVertices[3].position = Vector3(-1.0f,  1.0f, 0.0f);

			pVertices[0].normal =
			pVertices[1].normal =
			pVertices[2].normal =
			pVertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);

			pVertices[0].color =
			pVertices[1].color =
			pVertices[2].color =
			pVertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

			pVertices[0].texture = Vector2(1.0f, 0.0f);
			pVertices[1].texture = Vector2(1.0f, 1.0f);
			pVertices[2].texture = Vector2(0.0f, 0.0f);
			pVertices[3].texture = Vector2(0.0f, 1.0f);

			auto pDevice = Graphics::CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateVertexBuffer(pDevice, pVertices, sizeof(BillboardVertex) * m_vertexCount, &m_pVertexBuffer);
			Utility::SafeDelete(pVertices);
		}

		ID3D11Buffer* CBillboard::GetVertexBuffer() const
		{
			return m_pVertexBuffer;
		}

		int CBillboard::GetVertexCount() const
		{
			return m_vertexCount;
		}
	}
}