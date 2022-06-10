#include "MeshRenderTerrain.h"
#include "../../Provider/RenderProvider.h"
#include "../../Graphics/DirectX.h"

namespace Eternity
{
	namespace Component
	{
		CMeshRendererTerrain::CMeshRendererTerrain(GameObject::IGameObject& owner)
			: CMeshRenderer(owner)
		{
			Provider::CRenderProvider::GetInstance().Register(this, Provider::TERRAIN);
		}

		CMeshRendererTerrain::~CMeshRendererTerrain()
		{
		}

		void CMeshRendererTerrain::Attach(Graphics::CTerrain* pData)
		{
			m_pData = pData;
		}

		void CMeshRendererTerrain::Initialize() {}

		void CMeshRendererTerrain::Draw()
		{
			UINT stride = sizeof(Graphics::TerrainVertex);
			UINT offset = 0;

			auto pVertexBuffer = m_pData->GetVertexBuffer();
			auto pIndexBuffer = m_pData->GetIndexBuffer();
			auto indexCount = m_pData->GetVertexCount();
			auto sampler = m_pData->GetTexture(0)->GetSampler();
			auto pContext = Graphics::CDirectX::GetInstance().GetContext();

			for (UINT i = 0; i < 3; i++)
			{
				auto resources = m_pData->GetTexture(i)->GetResourceView();
				pContext->PSSetShaderResources(i, 1, &resources);
				pContext->PSSetSamplers(i, 1, &sampler);
			}

			pContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
			pContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			pContext->DrawIndexed(indexCount, 0, 0);
		}
	}
}