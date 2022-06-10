#pragma once

#include "../../Includer.h"
#include "../../Resources/Texture/WICTexture.h"
#include "../../Utility/UtilityBundle.h"
#include "MmdData.h"

namespace Eternity
{
	namespace Graphics
	{
		using namespace Resources;


		// ì«Ç›çûÇ›ñ{ëÃ
		class CPmdData
		{
		public:
			CPmdData();
			~CPmdData();
			void ReadFile(string path);

			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			vector<PmdVertex> m_vertices;
			vector<WORD> m_indices;
			vector<PmdMaterial> m_materials;
			vector<PmdBone> m_bones;
			vector<PmdIk> m_iks;
			vector<WORD> m_skins;
			vector<CWICTexture*> m_textures;
			vector<PmdBoneEx> m_exBones;
		private:
			void ReadHeader(ifstream* pIn);
			void ReadVertex(ifstream* pIn);
			void ReadIndex(ifstream* pIn);
			void ReadMaterial(ifstream* pIn);
			void ReadBone(ifstream* pIn);
			void ReadIK(ifstream* pIn);
			void ReadSkin(ifstream* pIn);
			void CreateBuffer();
			void CreateTexture();
			void CreateBoneMatrix();

			PmdHeader m_header;
			DWORD m_vertexCount;
			DWORD m_indexCount;
			DWORD m_materialCount;
			WORD m_boneCount;
			WORD m_ikCount;
			BYTE m_skinCount;
		};
	}
}