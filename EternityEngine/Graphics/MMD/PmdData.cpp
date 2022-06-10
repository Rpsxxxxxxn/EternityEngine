#include "PmdData.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		CPmdData::CPmdData()
			: m_vertexCount(0)
			, m_indexCount(0)
			, m_materialCount(0)
			, m_boneCount(0)
			, m_ikCount(0)
			, m_skinCount(0)
		{
		}

		CPmdData::~CPmdData()
		{
			for (auto i : m_textures)
				Utility::SafeDelete(i);

			m_vertices.clear();
			m_indices.clear();
			m_materials.clear();
			m_bones.clear();
			m_iks.clear();
			m_skins.clear();
			m_textures.clear();
		}

		void CPmdData::ReadFile(string path)
		{
			ifstream ifs(path, ios::binary);

			ReadHeader(&ifs);
			ReadVertex(&ifs);
			ReadIndex(&ifs);
			ReadMaterial(&ifs);
			ReadBone(&ifs);
			ReadIK(&ifs);
			CreateBuffer();
			CreateTexture();

			ifs.close();
		}

		void CPmdData::ReadHeader(ifstream* pIn)
		{
			pIn->read(m_header.magic, 3);
			pIn->read((char*)&m_header.version, sizeof(float));
			pIn->read(m_header.modelName, 20);
			pIn->read(m_header.comment, 256);
		}

		void CPmdData::ReadVertex(ifstream* pIn)
		{
			pIn->read((char*)&m_vertexCount, sizeof(DWORD));

			m_vertices.resize(m_vertexCount);

			for (DWORD i = 0; i < m_vertexCount; i++)
			{
				pIn->read((char*)m_vertices[i].position, sizeof(float) * 3);
				pIn->read((char*)m_vertices[i].normal, sizeof(float) * 3);
				pIn->read((char*)m_vertices[i].uv, sizeof(float) * 2);
				pIn->read((char*)m_vertices[i].boneNum, sizeof(WORD) * 2);
				pIn->read((char*)&m_vertices[i].boneWeight, sizeof(BYTE));
				pIn->read((char*)&m_vertices[i].edgeFlag, sizeof(BYTE));
			}
		}

		void CPmdData::ReadIndex(ifstream* pIn)
		{
			pIn->read((char*)&m_indexCount, sizeof(DWORD));

			m_indices.resize(m_indexCount);

			for (DWORD i = 0; i < m_indexCount; i++)
			{
				pIn->read((char*)&m_indices[i], sizeof(WORD));
			}
		}

		void CPmdData::ReadMaterial(ifstream* pIn)
		{
			pIn->read((char*)&m_materialCount, sizeof(DWORD));

			m_materials.resize(m_materialCount);

			for (DWORD i = 0; i < m_materialCount; i++)
			{
				pIn->read((char*)&m_materials[i].diffuse, sizeof(float) * 3);
				pIn->read((char*)&m_materials[i].alpha, sizeof(float));
				pIn->read((char*)&m_materials[i].power, sizeof(float));
				pIn->read((char*)&m_materials[i].specular, sizeof(float) * 3);
				pIn->read((char*)&m_materials[i].ambient, sizeof(float) * 3);
				pIn->read((char*)&m_materials[i].toonIndex, sizeof(BYTE));
				pIn->read((char*)&m_materials[i].edgeFlag, sizeof(BYTE));
				pIn->read((char*)&m_materials[i].faceVertexCount, sizeof(DWORD));

				char buffer[20];
				pIn->read((char*)&buffer, sizeof(char) * 20);
				m_materials[i].textureFileName = buffer;
			}
		}

		void CPmdData::ReadBone(ifstream* pIn)
		{
			pIn->read((char*)&m_boneCount, sizeof(WORD));

			m_bones.resize(m_boneCount);

			for (DWORD i = 0; i < m_boneCount; i++)
			{
				pIn->read((char*)&m_bones[i].boneName, sizeof(char) * 20);
				pIn->read((char*)&m_bones[i].parentBoneIndex, sizeof(WORD));
				pIn->read((char*)&m_bones[i].tailPosBoneIndex, sizeof(WORD));
				pIn->read((char*)&m_bones[i].boneType, sizeof(BYTE));
				pIn->read((char*)&m_bones[i].ikParentBoneIndex, sizeof(WORD));
				pIn->read((char*)&m_bones[i].boneHeadPosition, sizeof(float) * 3);
			}
		}

		void CPmdData::ReadIK(ifstream* pIn)
		{
			pIn->read((char*)&m_ikCount, sizeof(WORD));

			m_iks.resize(m_ikCount);

			for (DWORD i = 0; i < m_ikCount; i++)
			{
				pIn->read((char*)&m_iks[i].boneIndex, sizeof(WORD));
				pIn->read((char*)&m_iks[i].targetBoneIndex, sizeof(WORD));
				pIn->read((char*)&m_iks[i].chainCount, sizeof(BYTE));
				pIn->read((char*)&m_iks[i].recursiveCount, sizeof(WORD));
				pIn->read((char*)&m_iks[i].controlWeight, sizeof(float));
			}
		}

		void CPmdData::ReadSkin(ifstream* pIn)
		{
			pIn->read((char*)&m_skinCount, sizeof(BYTE));

			m_skins.resize(m_skinCount);

			for (BYTE i = 0; i < m_skinCount; i++)
			{
				pIn->read((char*)&m_skins[i], sizeof(WORD));
			}
		}

		void CPmdData::CreateBuffer()
		{
			MMDVertex* pVertices = new MMDVertex[m_vertexCount];

			for (UINT i = 0; i < m_vertexCount; i++)
			{
				pVertices[i].position.x = m_vertices[i].position[0];
				pVertices[i].position.y = m_vertices[i].position[1];
				pVertices[i].position.z = m_vertices[i].position[2];
				pVertices[i].normal.x = m_vertices[i].normal[0];
				pVertices[i].normal.y = m_vertices[i].normal[1];
				pVertices[i].normal.z = m_vertices[i].normal[2];
				pVertices[i].color.x = 0.5f;
				pVertices[i].color.y = 0.5f;
				pVertices[i].color.z = 0.5f;
				pVertices[i].color.w = 1.0f;
				pVertices[i].texture.x = m_vertices[i].uv[0];
				pVertices[i].texture.y = m_vertices[i].uv[1];
			}

			WORD* pIndices = new WORD[m_indexCount];

			for (UINT i = 0; i < m_indexCount; i++)
			{
				pIndices[i] = m_indices[i];
			}

			UINT countIndex = 0;

			for (DWORD i = 0; i < m_materialCount; i++)
			{
				for (DWORD j = 0; j <m_materials[i].faceVertexCount; j++)
				{
					WORD face = m_indices[countIndex];
					pVertices[face].color.x = m_materials[i].diffuse[0];
					pVertices[face].color.y = m_materials[i].diffuse[1];
					pVertices[face].color.z = m_materials[i].diffuse[2];
					pVertices[face].color.w = m_materials[i].alpha;
					countIndex++;
				}
			}

			auto pDevice = Graphics::CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateVertexBuffer(pDevice, pVertices, sizeof(MMDVertex) * m_vertexCount, &m_pVertexBuffer);
			Utility::CHelper::CreateIndexBuffer(pDevice, pIndices, sizeof(WORD) * m_indexCount, &m_pIndexBuffer);
		
			Utility::SafeDeleteArray(pVertices);
			Utility::SafeDeleteArray(pIndices);
		}

		void CPmdData::CreateTexture()
		{
			m_textures.resize(m_materialCount);

			for (DWORD i = 0; i < m_materialCount; i++)
			{
				string srcPath = "Assets/Model/" + m_materials[i].textureFileName;

				m_textures[i] = new CWICTexture;
				m_textures[i]->Create(srcPath);
				m_textures[i]->SetSampler(
					D3D11_FILTER_MIN_MAG_MIP_LINEAR,
					D3D11_TEXTURE_ADDRESS_CLAMP,
					D3D11_COMPARISON_NEVER,
					0,
					FLT_MAX);
			}
		}

		void CPmdData::CreateBoneMatrix()
		{
			m_exBones.resize(m_boneCount);
			for (UINT i = 0; i < m_boneCount; ++i)
			{
				int parentIndex(-1), firstChildIndex(-1), siblingIndex(-1);
				if (m_bones[i].parentBoneIndex != 0xffff)
					parentIndex = m_bones[i].parentBoneIndex;

				for (UINT j = i + 1; j < m_boneCount; j++)
				{
					if (m_bones[i].parentBoneIndex == m_bones[j].parentBoneIndex)
					{
						siblingIndex = j;
						break;
					}
				}

				for (unsigned int j = 0; j < m_boneCount; ++j) {
					if (i == m_bones[j].parentBoneIndex) {
						firstChildIndex = j;
						break;
					}
				}

				Matrix modelLocalInitMat = XMMatrixTranslation(m_bones[i].boneHeadPosition[0], m_bones[i].boneHeadPosition[1], m_bones[i].boneHeadPosition[2]);
				char boneName[21] = { 0 };	// ボーン名が20byteのときのために最後に0を追加
				memcpy(boneName, m_bones[i].boneName, 20);
				m_exBones[i].id = i;
				if (parentIndex != -1) m_exBones[i].parent = &m_exBones[parentIndex];
				if (firstChildIndex != -1) m_exBones[i].firstChild = &m_exBones[firstChildIndex];
				if (siblingIndex != -1) m_exBones[i].sibling = &m_exBones[siblingIndex];
				m_exBones[i].name = boneName;
				m_exBones[i].type = m_bones[i].boneType;
				m_exBones[i].initMatrixModelLocal = m_exBones[i].initMatrixBoneLocal = modelLocalInitMat;	// モデルローカル座標系

				m_exBones[i].offsetMatrixModelLocal = XMMatrixInverse(0, m_exBones[i].initMatrixModelLocal);

				class InitMatCalc {	// InitMatをボーンローカル座標系に変換する再帰関数を定義したクラス
				public:
					static void Run(Bone* me, D3DXMATRIX* parentoffsetMat) {
						if (me->firstChild) Run(me->firstChild, &me->offsetMatML);
						if (me->sibling)	Run(me->sibling, parentoffsetMat);
						if (parentoffsetMat) me->initMatBL *= *parentoffsetMat;
					}
				};
				InitMatCalc::Run(&bones[0], 0);	// ボーンローカル座標系に変換
				for (unsigned int i = 0; i < size; ++i) bones[i].boneMatBL = bones[i].initMatBL;
			}
		}
	}
}