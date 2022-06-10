#pragma once

#include "MeshRender.h"
#include "../../Graphics/Terrain/Terrain.h"

namespace Eternity
{
	namespace Component
	{
		class CMeshRendererTerrain : public CMeshRenderer
		{
		public:
			CMeshRendererTerrain(GameObject::IGameObject&);
			~CMeshRendererTerrain();
			void Attach(Graphics::CTerrain* pTerrain);
			void Initialize();
			void Draw();
		private:
			Graphics::CTerrain* m_pData;
			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			UINT m_vertexCount;
			UINT m_indexCount;
		};
	}
}