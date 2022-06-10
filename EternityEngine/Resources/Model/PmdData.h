#pragma once

#include "../../CommonLib.h"
#include "../Texture/Texture.h"

namespace Resources
{
	struct PmdHeader
	{
		char magic[3];
		float version;
		char modelName[20];
		char comment[256];
	};

	struct PmdVertex
	{
		float position[3];
		float normal[3];
		float uv[2];
		WORD boneNum[2];
		BYTE boneWeight;
		BYTE edgeFlag;
	};

	struct PmdMaterial
	{
		float diffuse[3];
		float alpha;
		float power;
		float specular[3];
		float ambient[3];
		BYTE toonIndex;
		BYTE edgeFlag;
		DWORD faceVertexCount;
		string textureFileName;
	};

	struct PmdBone
	{
		char boneName[20];
		WORD parentBoneIndex;
		WORD tailPosBoneIndex;
		BYTE boneType;
		WORD ikParentBoneIndex;
		float boneHeadPosition[3];
	};

	struct PmdIk
	{
		WORD boneIndex;
		WORD targetBoneIndex;
		BYTE chainCount;
		WORD recursiveCount;
		float controlWeight;
	};

	class PmdData
	{
		PmdHeader m_header;
		DWORD m_vertexCount;
		DWORD m_indexCount;
		DWORD m_materialCount;
		WORD m_boneCount;
		WORD m_ikCount;
		BYTE m_skinCount;
	public:
		PmdData();
		~PmdData();
		void Load(string);

		vector<PmdVertex> m_vertices;
		vector<WORD> m_indices;
		vector<PmdMaterial> m_materials;
		vector<PmdBone> m_bones;
		vector<PmdIk> m_iks;
		vector<WORD> m_skins;
		vector<TextureData*> m_textures;
	private:
		void ReadHeader(ifstream*);
		void ReadVertex(ifstream*);
		void ReadIndex(ifstream*);
		void ReadMaterial(ifstream*);
		void ReadBone(ifstream*);
		void ReadIK(ifstream*);
		void ReadSkin(ifstream*);
		void CreateTexture();
	};
}