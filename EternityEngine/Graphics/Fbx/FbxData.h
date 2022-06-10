#pragma once

#include "../../Includer.h"
#include "../../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Graphics
	{
		struct FbxVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector4 color;
			Vector2 texture;
		};

		class CFbxData
		{
		public:
			CFbxData();
			~CFbxData();
			void Create(string path);
		private:
			void InitializeImporter(string path);
			void ReadVertex();
			void ReadIndex();
			void ReadNormal();
			void ReadUVTexture();
			void ReadUV();
			void ReadMaterial();
			void CreateBuffer();
			void CreateBoneMatrix();
			void TriangleRecursive(FbxNode* pNode);

			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			FbxManager* m_pManager;
			FbxScene* m_pScene;
			FbxMesh* m_pMesh;
			FbxMatrix* m_pBoneMatrix;
			vector<FbxMatrix> m_boneMatrix;
			vector<FbxVertex> m_vertices;
			int m_numVertexCount;
			int m_numIndexCount;
			int* m_pIndices;
		public:
			ID3D11Buffer* GetVertexBuffer() const { return m_pVertexBuffer; };
			ID3D11Buffer* GetIndexBuffer() const { return m_pIndexBuffer; };
			int* GetIndices() const { return m_pIndices; };
			int GetVertexCount() const { return m_numVertexCount; };
			int GetIndexCount() const { return m_numIndexCount; };
		};
	}
}