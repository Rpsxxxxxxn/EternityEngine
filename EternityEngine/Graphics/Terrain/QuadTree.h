#pragma once

#include "../../Includer.h"
#include "../../Resources/Texture/WICTexture.h"
#include "../../Utility/UtilityBundle.h"
#include "Terrain.h"

namespace Eternity
{
	namespace Graphics
	{
		struct NodeType
		{
			float posX;
			float posZ;
			float width;
			int indexCount;
			ID3D11Buffer* pVertexBuffer;
			ID3D11Buffer* pIndexBuffer;
			NodeType* pNodes[4];
		};

		class CQuadTree
		{
		public:
			static const int MAX_TRIANGLES;
			CQuadTree();
			~CQuadTree();
			bool Create(CTerrain* pTerrain);
			void Release(NodeType* pNode);

			int GetIndexCount();
			TerrainVertex* GetVertexArray();
			CWICTexture* GetTexture(int index);
			NodeType* GetParentNode();
		private:
			void CreateTexture(const UINT index, string path);
			void CalcMeshDimensions(int vertexCount, float& centerX, float& centerZ, float& meshWidth);
			void CreateTreeNode(NodeType* pNode, float posX, float posZ, float width);
			int CountTriangles(float posX, float posZ, float width);
			bool IsTriangleContained(int index, float posX, float posZ, float width);

			int m_indexCount;
			int m_drawCount;
			CWICTexture* m_pTextureData[3];
			TerrainVertex* m_pVertices;
			NodeType* m_pParentNode;
		};
	}
}