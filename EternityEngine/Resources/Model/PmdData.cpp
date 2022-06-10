#include "PmdData.h"

namespace Resources
{
	PmdData::PmdData()
		: m_vertexCount(0)
		, m_indexCount(0)
		, m_materialCount(0) {};

	PmdData::~PmdData()
	{
		for (auto i : m_textures)
			Utility::SafeDelete(i);

		m_vertices.clear();
		m_indices.clear();
		m_materials.clear();
		m_textures.clear();
	};

	void PmdData::Load(string _path)
	{
		ifstream ifs;
		ifs.open(_path, ios::binary);

		ReadHeader(&ifs);
		ReadVertex(&ifs);
		ReadIndex(&ifs);
		ReadMaterial(&ifs);
		ReadBone(&ifs);
		ReadIK(&ifs);

		CreateTexture();

		ifs.close();
	}

	void PmdData::ReadHeader(ifstream* pIn)
	{
		pIn->read(m_header.magic, 3);
		pIn->read((char*)&m_header.version, sizeof(float));
		pIn->read(m_header.modelName, 20);
		pIn->read(m_header.comment, 256);
	}

	void PmdData::ReadVertex(ifstream* pIn)
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

	void PmdData::ReadIndex(ifstream* pIn)
	{
		pIn->read((char*)&m_indexCount, sizeof(DWORD));

		m_indices.resize(m_indexCount);

		for (DWORD i = 0; i < m_indexCount; i++)
		{
			pIn->read((char*)&m_indices[i], sizeof(WORD));
		}
	}

	void PmdData::ReadMaterial(ifstream* pIn)
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

	void PmdData::ReadBone(ifstream* pIn)
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

	void PmdData::ReadIK(ifstream* pIn)
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

	void PmdData::ReadSkin(ifstream* pIn)
	{
		pIn->read((char*)&m_skinCount, sizeof(BYTE));

		m_skins.resize(m_skinCount);

		for (BYTE i = 0; i < m_skinCount; i++)
		{
			pIn->read((char*)&m_skins[i], sizeof(WORD));
		}
	}

	void PmdData::CreateTexture()
	{
		m_textures.resize(m_materialCount);

		for (DWORD i = 0; i < m_materialCount; i++)
		{
			string srcPath = "Assets/Model/" + m_materials[i].textureFileName;

			m_textures[i] = new TextureData;
			m_textures[i]->Create(srcPath);
			m_textures[i]->SetSampler(
				D3D11_FILTER_MIN_MAG_MIP_LINEAR,
				D3D11_TEXTURE_ADDRESS_CLAMP,
				D3D11_COMPARISON_NEVER,
				0,
				FLT_MAX);
		}
	}
}