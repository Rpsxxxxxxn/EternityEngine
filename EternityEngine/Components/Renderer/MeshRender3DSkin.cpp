#include "MeshRender3DSkin.h"
#include "../../Provider/RenderProvider.h"

namespace Eternity
{
	namespace Component
	{
		CMeshRenderer3DSkin::CMeshRenderer3DSkin(GameObject::IGameObject& owner)
			: CMeshRenderer(owner)
		{
			Provider::CRenderProvider::GetInstance().Register(this, Provider::SKIN_MESH);
		}

		CMeshRenderer3DSkin::~CMeshRenderer3DSkin() {}

		void CMeshRenderer3DSkin::Attach(Graphics::CPmdData* pData)
		{
			m_pData = pData;
		}

		void CMeshRenderer3DSkin::Initialize() {}

		void CMeshRenderer3DSkin::Draw()
		{
			m_startIndex = 0;

			for (DWORD i = 0; i < m_pData->m_materials.size(); i++)
			{
				DrawMesh(i);
			}
		}

		void CMeshRenderer3DSkin::DrawMesh(const UINT index)
		{
			UINT stride = sizeof(Graphics::MMDVertex);
			UINT offset = 0;

			auto pContext = Graphics::CDirectX::GetInstance().GetContext();
			pContext->IASetVertexBuffers(0, 1, &m_pData->m_pVertexBuffer, &stride, &offset);
			pContext->IASetIndexBuffer(m_pData->m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
			pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			auto resource = m_pData->m_textures[index]->GetResourceView();
			auto sampler = m_pData->m_textures[index]->GetSampler();
			pContext->PSSetShaderResources(0, 1, &resource);
			pContext->PSSetSamplers(0, 1, &sampler);
			pContext->DrawIndexed(m_pData->m_materials[index].faceVertexCount, m_startIndex, 0);

			m_startIndex += m_pData->m_materials[index].faceVertexCount;
		}
	}
}