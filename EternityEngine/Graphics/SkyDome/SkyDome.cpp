#include "SkyDome.h"

namespace Eternity
{
	namespace Graphics
	{
		CSkyDome::CSkyDome()
			: m_pVertices(nullptr)
			, m_pVertexBuffer(nullptr)
			, m_pIndexBuffer(nullptr)
			, m_apexColor(Vector4::Zero)
			, m_centerColor(Vector4::Zero)
			, m_vertexCount(0)
			, m_indexCount(0)
		{
		}

		CSkyDome::~CSkyDome()
		{
			Utility::SafeDelete(m_pVertices);
			Utility::SafeRelease(m_pVertexBuffer);
			Utility::SafeRelease(m_pIndexBuffer);
		}

		void CSkyDome::Create()
		{
			CreateVertex();
			CreateBuffer();
		}

		void CSkyDome::CreateVertex()
		{
		}

		void CSkyDome::CreateBuffer()
		{
		}
	}
}