#pragma once

#include "../../Includer.h"
#include "../../Resources/Texture/WICTexture.h"
#include "../../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Graphics
	{
		using namespace Resources;

		struct TerrainVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector4 color;
			Vector2 texture;
		};

		// パーリンノイズによる自動地形生成
		class CTerrain
		{
		public:
			CTerrain();
			~CTerrain();
			void Create();
		private:
			void CreateTerrain();
			void CreateVertex();
			void CreateTexture(int index, string path);
			void CreateBuffer();
			void CalculateNormal();
			void CalculateTextureCoord();
			void SetVertex(int j, int i, float tu, float tv);

			Utility::CPerlinNoise m_perlin;
			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			TerrainVertex* m_pHeightMaps;
			TerrainVertex* m_pVertices;
			DWORD* m_pIndices;
			CWICTexture* m_pTextureData[3];
			std::uint32_t m_width;
			std::uint32_t m_height;
			std::uint32_t m_vertexCount;
			std::uint32_t m_seed;
			double m_frequency;
			int m_octaves;
			float m_heightScale;
			float m_widthScale;
		public:
			ID3D11Buffer* GetVertexBuffer();
			ID3D11Buffer* GetIndexBuffer();
			CWICTexture* GetTexture(UINT index);
			int GetVertexCount();
		};
	}
}