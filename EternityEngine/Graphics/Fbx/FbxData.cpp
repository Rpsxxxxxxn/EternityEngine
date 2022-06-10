#include "FbxData.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		CFbxData::CFbxData()
			: m_pManager(nullptr)
			, m_pScene(nullptr)
			, m_pMesh(nullptr)
		{
		}

		CFbxData::~CFbxData()
		{
			Utility::SafeDeleteArray(m_pBoneMatrix);
			m_pScene->Destroy();
			m_pManager->Destroy();
		}

		void CFbxData::Create(string path)
		{
			InitializeImporter(path);
			ReadVertex();
			ReadIndex();
			ReadNormal();
			ReadUV();
			ReadMaterial();
			CreateBuffer();
			CreateBoneMatrix();
		}

		void CFbxData::InitializeImporter(string path)
		{
			m_pManager = FbxManager::Create();
			m_pScene = FbxScene::Create(m_pManager, "fbxScene");
			FbxImporter* pFbxImporter = FbxImporter::Create(m_pManager, "imp");
			pFbxImporter->Initialize(path.c_str(), -1, m_pManager->GetIOSettings());

			if (!pFbxImporter->Import(m_pScene))
			{
				return;
			}

			FbxAxisSystem SceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem();
			if (SceneAxisSystem != FbxAxisSystem::DirectX)
			{
				FbxAxisSystem::DirectX.ConvertScene(m_pScene);
			}

			FbxSystemUnit SceneSystemUnit = m_pScene->GetGlobalSettings().GetSystemUnit();
			if (SceneSystemUnit.GetScaleFactor() != 1.0f)
			{
				FbxSystemUnit::cm.ConvertScene(m_pScene);
			}

			// 三角形に変換
			TriangleRecursive(m_pScene->GetRootNode());

			pFbxImporter->Destroy();
		}

		void CFbxData::ReadVertex()
		{
			auto rootNode = m_pScene->GetRootNode();
			for (int i = 0; i < rootNode->GetChildCount(); i++)
			{
				if (rootNode->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				{
					m_pMesh = rootNode->GetChild(i)->GetMesh();
					break;
				}
			}

			m_numVertexCount = m_pMesh->GetControlPointsCount();
			m_vertices.resize(m_numVertexCount);

			for (int i = 0; i < m_numVertexCount; i++)
			{
				m_vertices[i].position.x = static_cast<float>(m_pMesh->GetControlPointAt(i)[0]);
				m_vertices[i].position.y = static_cast<float>(m_pMesh->GetControlPointAt(i)[1]);
				m_vertices[i].position.z = static_cast<float>(m_pMesh->GetControlPointAt(i)[2]);
			}
		}

		void CFbxData::ReadIndex()
		{
			m_numIndexCount = m_pMesh->GetPolygonVertexCount();
			m_pIndices = m_pMesh->GetPolygonVertices();
		}

		void CFbxData::ReadNormal()
		{
			FbxArray<FbxVector4> normals;

			m_pMesh->GetPolygonVertexNormals(normals);

			int normalCount = normals.Size();

			for (int i = 0; i < normalCount; i++)
			{
				m_vertices[m_pIndices[i]].normal.x = static_cast<float>(normals[i][0]);
				m_vertices[m_pIndices[i]].normal.y = static_cast<float>(normals[i][1]);
				m_vertices[m_pIndices[i]].normal.z = static_cast<float>(normals[i][2]);
			}
		}

		void CFbxData::ReadUVTexture()
		{
			FbxStringList uvsetName;

			m_pMesh->GetUVSetNames(uvsetName);
		}

		void CFbxData::ReadUV()
		{
			FbxStringList uvsetName;
			m_pMesh->GetUVSetNames(uvsetName);

			FbxArray<FbxVector2> uvsets;
			m_pMesh->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

			int uvsetCount = uvsets.Size();

			for (int i = 0; i < uvsetCount; i++)
			{
				m_vertices[m_pIndices[i]].texture.x = static_cast<float>(uvsets[i][0]);
				m_vertices[m_pIndices[i]].texture.y = static_cast<float>(uvsets[i][1]);
			}
		}

		void CFbxData::ReadMaterial()
		{
			FbxNode* pNode = m_pMesh->GetNode();

			int materialCount = pNode->GetMaterialCount();

			for (int i = 0; i < materialCount; ++i)
			{
				FbxSurfaceMaterial* pMat = pNode->GetMaterial(i);

				const FbxProperty lProperty;
				pMat->FindProperty(FbxSurfaceMaterial::sEmissive);
				pMat->FindProperty(FbxSurfaceMaterial::sAmbient);
				pMat->FindProperty(FbxSurfaceMaterial::sDiffuse);
				pMat->FindProperty(FbxSurfaceMaterial::sSpecular);

				const FbxProperty lFactorProperty;
				pMat->FindProperty(FbxSurfaceMaterial::sEmissiveFactor);
				pMat->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
				pMat->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
				pMat->FindProperty(FbxSurfaceMaterial::sSpecularFactor);

				FbxDouble3 lResoult = lProperty.Get<FbxDouble3>();
				double lFactor = lFactorProperty.Get<FbxDouble>();

				lProperty.IsValid();

				FbxProperty lTransparencyFactorProperty = pMat->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
				if (lTransparencyFactorProperty.IsValid())
				{
					double lTransparencyFactor = lTransparencyFactorProperty.Get<FbxDouble>();
				}

				FbxProperty lShininessProperty = pMat->FindProperty(FbxSurfaceMaterial::sShininess);
				if (lShininessProperty.IsValid())
				{
					double lShininess = lShininessProperty.Get<FbxDouble>();
				}

				// テクスチャ情報の取得
				int textureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();
				for (int i = 0; i < textureCount; ++i)
				{
					FbxFileTexture* pTexture = lProperty.GetSrcObject<FbxFileTexture>(i);
					if (!pTexture) continue;

					FbxString uvSetName = pTexture->UVSet.Get();
					string uvSetString = uvSetName.Buffer();
					string path = pTexture->GetFileName();
				}

				const int sLayeredTextureCount = lProperty.GetSrcObjectCount<FbxLayeredTexture>();
				for (int i = 0; i < sLayeredTextureCount; ++i)
				{
					FbxLayeredTexture* lLayeredTexture = lProperty.GetSrcObject<FbxLayeredTexture>(i);
					int sTextureFileCount = lLayeredTexture->GetSrcObjectCount<FbxFileTexture>();

					for (int j = 0; j < sTextureFileCount; ++j)
					{
						FbxFileTexture* pFileTexture = lLayeredTexture->GetSrcObject<FbxFileTexture>(j);
						if (!pFileTexture) continue;

						FbxString uvSetName = pFileTexture->UVSet.Get();
						string uvSetString = uvSetName.Buffer();
						string path = pFileTexture->GetFileName();
					}
				}
			}
		}

		void CFbxData::CreateBuffer()
		{
			FbxVertex* pVertices = new FbxVertex[m_numVertexCount];

			for (int i = 0; i < m_numVertexCount; ++i)
			{
				pVertices[i].position = m_vertices[i].position;
				pVertices[i].normal = m_vertices[i].normal;
				pVertices[i].texture = m_vertices[i].texture;
			}

			auto pDevice = Graphics::CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateVertexBuffer(pDevice, pVertices, sizeof(FbxVertex) * m_numVertexCount, &m_pVertexBuffer);
			Utility::CHelper::CreateIndexBuffer(pDevice, m_pIndices, sizeof(int) * m_numIndexCount, &m_pIndexBuffer);

			Utility::SafeDelete(pVertices);
		}
		
		void CFbxData::CreateBoneMatrix()
		{
			m_pBoneMatrix = new FbxMatrix[m_numVertexCount];
			memset(m_pBoneMatrix, 0, sizeof(FbxMatrix) * m_numVertexCount);
		}

		void CFbxData::TriangleRecursive(FbxNode* pNode)
		{
			FbxNodeAttribute* pNodeAttribute = pNode->GetNodeAttribute();

			if (pNodeAttribute)
			{
				FbxNodeAttribute::EType type = pNodeAttribute->GetAttributeType();

				if (type == FbxNodeAttribute::eMesh ||
					type == FbxNodeAttribute::eNurbs ||
					type == FbxNodeAttribute::eNurbsSurface ||
					type == FbxNodeAttribute::ePatch)
				{
					FbxGeometryConverter lConverter(pNode->GetFbxManager());
					lConverter.Triangulate(m_pScene, true);
				}
			}

			// 子ノードの探索
			const int lChildCount = pNode->GetChildCount();
			for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
			{
				TriangleRecursive(pNode->GetChild(lChildIndex));
			}
		}
	}
}