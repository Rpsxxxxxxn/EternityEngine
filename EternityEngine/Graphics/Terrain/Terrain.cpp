#include "Terrain.h"
#include "../DirectX.h"

namespace Eternity
{
	namespace Graphics
	{
		constexpr int TEXTURE_REPEAT = 64;

		CTerrain::CTerrain()
			: m_width(128)
			, m_height(128)
			, m_vertexCount(0)
			, m_seed(123)
			, m_frequency(2.0)
			, m_octaves(4)
			, m_heightScale(15.0f)
			, m_widthScale(1.0f)
		{
			for (std::uint32_t i = 0; i < 3; ++i)
				m_pTextureData[i] = new CWICTexture;
		}

		CTerrain::~CTerrain()
		{
			Utility::SafeRelease(m_pVertexBuffer);
			Utility::SafeRelease(m_pIndexBuffer);
			Utility::SafeDeleteArray(m_pHeightMaps);
			Utility::SafeDeleteArray(m_pVertices);
			Utility::SafeDeleteArray(m_pIndices);

			for (std::uint32_t i = 0; i < 3; ++i)
				Utility::SafeDelete(m_pTextureData[i]);
		}

		void CTerrain::Create()
		{
			CreateTerrain();
			CalculateTextureCoord();
			CalculateNormal();
			CreateVertex();
			CreateBuffer();
			CreateTexture(0, "Assets/Image/bn7rz-1irv8.png");
			CreateTexture(1, "Assets/Image/b35rv-whlaq.png");
			CreateTexture(2, "Assets/Image/bt5wv-i27hq.png");
		}

		ID3D11Buffer* CTerrain::GetVertexBuffer()
		{
			return m_pVertexBuffer;
		}

		ID3D11Buffer* CTerrain::GetIndexBuffer()
		{
			return m_pIndexBuffer;
		}

		CWICTexture* CTerrain::GetTexture(UINT index)
		{
			return m_pTextureData[index];
		}

		int CTerrain::GetVertexCount()
		{
			return m_vertexCount;
		}

		void CTerrain::CreateTerrain()
		{
			m_vertexCount = (m_width - 1) * (m_height - 1) * 6;

			m_pVertices = new TerrainVertex[m_vertexCount];
			m_pIndices = new DWORD[m_vertexCount];
			m_pHeightMaps = new TerrainVertex[m_width * m_height];

			m_perlin.ReSeed(m_seed);

			double fx = m_width / m_frequency;
			double fy = m_height / m_frequency;

			int index = 0;

			for (UINT j = 0; j < m_width; j++)
			{
				for (UINT i = 0; i < m_height; i++)
				{
					auto noise = m_perlin.OctaveNoise(i / fx, j / fy, m_octaves);
					m_pHeightMaps[index].position.x = (float)(i * m_widthScale);
					m_pHeightMaps[index].position.y = (float)(noise * m_heightScale);
					m_pHeightMaps[index].position.z = (float)(j * m_widthScale);
					index++;
				}
			}
		}

		void CTerrain::CreateVertex()
		{
			float tu = 0.0f;
			float tv = 0.0f;
			int index = 0;

			for (UINT j = 0; j < (m_height - 1); j++)
			{
				for (UINT i = 0; i < (m_width - 1); i++)
				{
					int index1 = (m_height * j) + i;			// bl
					int index2 = (m_height * j) + (i + 1);		// br
					int index3 = (m_height * (j + 1)) + i;		// ul
					int index4 = (m_height * (j + 1)) + (i + 1);// ur

					//▼左上 ul
					tu = m_pHeightMaps[index3].texture.x;
					tv = m_pHeightMaps[index3].texture.y;
					if (tv == 1.0f) { tv = 0.0f; }
					SetVertex(index3, index++, tu, tv);

					//▼右上 ur
					tu = m_pHeightMaps[index4].texture.x;
					tv = m_pHeightMaps[index4].texture.y;
					if (tu == 0.0f) { tu = 1.0f; }
					if (tv == 1.0f) { tv = 0.0f; }
					SetVertex(index4, index++, tu, tv);

					//▼左下 bl
					tu = m_pHeightMaps[index1].texture.x;
					tv = m_pHeightMaps[index1].texture.y;
					SetVertex(index1, index++, tu, tv);

					//▼左下 bl
					tu = m_pHeightMaps[index1].texture.x;
					tv = m_pHeightMaps[index1].texture.y;
					SetVertex(index1, index++, tu, tv);

					//▼右上 ur
					tu = m_pHeightMaps[index4].texture.x;
					tv = m_pHeightMaps[index4].texture.y;
					if (tu == 0.0f) { tu = 1.0f; }
					if (tv == 1.0f) { tv = 0.0f; }
					SetVertex(index4, index++, tu, tv);

					//▼右下 br
					tu = m_pHeightMaps[index2].texture.x;
					tv = m_pHeightMaps[index2].texture.y;
					if (tu == 0.0f) { tu = 1.0f; }
					SetVertex(index2, index++, tu, tv);
				}
			}
		}

		void CTerrain::CreateTexture(int index, string path)
		{
			m_pTextureData[index]->Create(path);

			CD3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			m_pTextureData[index]->SetSampler(samplerDesc);
		}

		void CTerrain::CreateBuffer()
		{
			TerrainVertex* pVertices = new TerrainVertex[m_vertexCount];
			DWORD* pIndices = new DWORD[m_vertexCount];

			for (std::uint32_t i = 0; i < m_vertexCount; i++)
			{
				pVertices[i].position = m_pVertices[i].position;
				pVertices[i].normal = m_pVertices[i].normal;
				pVertices[i].texture = m_pVertices[i].texture;
				pIndices[i] = m_pIndices[i];
			}

			auto pDevice = Graphics::CDirectX::GetInstance().GetDevice();
			Utility::CHelper::CreateVertexBuffer(pDevice, pVertices, sizeof(TerrainVertex) * m_vertexCount, &m_pVertexBuffer);
			Utility::CHelper::CreateIndexBuffer(pDevice, pIndices, sizeof(DWORD) * m_vertexCount, &m_pIndexBuffer);

			Utility::SafeDeleteArray(pVertices);
			Utility::SafeDeleteArray(pIndices);
		}

		void CTerrain::CalculateNormal()
		{
			struct Vertex
			{
				Vector3 position;
			};

			int index, count;
			float vertex1[3], vertex2[3], vertex3[3], vector1[3], vector2[3];
			Vertex* normals = new Vertex[(m_height - 1) * (m_width - 1)];

			for (int j = 0; j < (int)(m_height - 1); j++)
			{
				for (int i = 0; i < (int)(m_width - 1); i++)
				{
					UINT index1 = (j * m_height) + i;
					UINT index2 = (j * m_height) + (i + 1);
					UINT index3 = ((j + 1) * m_height) + i;

					vertex1[0] = m_pHeightMaps[index1].position.x;
					vertex1[1] = m_pHeightMaps[index1].position.y;
					vertex1[2] = m_pHeightMaps[index1].position.z;

					vertex2[0] = m_pHeightMaps[index2].position.x;
					vertex2[1] = m_pHeightMaps[index2].position.y;
					vertex2[2] = m_pHeightMaps[index2].position.z;

					vertex3[0] = m_pHeightMaps[index3].position.x;
					vertex3[1] = m_pHeightMaps[index3].position.y;
					vertex3[2] = m_pHeightMaps[index3].position.z;

					vector1[0] = vertex1[0] - vertex3[0];
					vector1[1] = vertex1[1] - vertex3[1];
					vector1[2] = vertex1[2] - vertex3[2];
					vector2[0] = vertex3[0] - vertex2[0];
					vector2[1] = vertex3[1] - vertex2[1];
					vector2[2] = vertex3[2] - vertex2[2];

					index = (j * (m_height - 1)) + i;

					normals[index].position.x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
					normals[index].position.y = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
					normals[index].position.z = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
				}
			}

			float sum[3];

			for (int j = 0; j < (int)(m_height); j++)
			{
				for (int i = 0; i < (int)(m_width); i++)
				{
					sum[0] = 0.0f;
					sum[1] = 0.0f;
					sum[2] = 0.0f;

					count = 0;

					//▼左下
					if (((i - 1) >= 0) && ((j - 1) >= 0))
					{
						index = ((j - 1) * (int)(m_height - 1)) + (i - 1);

						sum[0] += normals[index].position.x;
						sum[1] += normals[index].position.y;
						sum[2] += normals[index].position.z;
						count++;
					}

					//▼右下
					if ((i < (int)(m_width - 1)) && ((j - 1) >= 0))
					{
						index = ((j - 1) * (m_height - 1)) + i;

						sum[0] += normals[index].position.x;
						sum[1] += normals[index].position.y;
						sum[2] += normals[index].position.z;
						count++;
					}

					//▼左上
					if (((i - 1) >= 0) && (j < (int)(m_height - 1)))
					{
						index = (j * (int)(m_height - 1)) + (i - 1);

						sum[0] += normals[index].position.x;
						sum[1] += normals[index].position.y;
						sum[2] += normals[index].position.z;
						count++;
					}

					//▼右上
					if ((i < (int)(m_width - 1)) && (j < (int)(m_height - 1)))
					{
						index = (j * (int)(m_height - 1)) + i;

						sum[0] += normals[index].position.x;
						sum[1] += normals[index].position.y;
						sum[2] += normals[index].position.z;
						count++;
					}

					sum[0] = (sum[0] / (float)count);
					sum[1] = (sum[1] / (float)count);
					sum[2] = (sum[2] / (float)count);

					float length = sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));

					index = (j * m_height) + i;

					m_pHeightMaps[index].normal.x = (sum[0] / length);
					m_pHeightMaps[index].normal.y = (sum[1] / length);
					m_pHeightMaps[index].normal.z = (sum[2] / length);
				}
			}
			Utility::SafeDeleteArray(normals);
		}

		void CTerrain::CalculateTextureCoord()
		{
			float incrementValue = (float)TEXTURE_REPEAT / (float)m_width;

			int incrementCount = m_width / TEXTURE_REPEAT;

			float tuCoordinate = 0.0f;
			float tvCoordinate = 1.0f;

			int tuCount = 0;
			int tvCount = 0;

			for (int j = 0; j < (int)(m_height); j++)
			{
				for (int i = 0; i < (int)(m_width); i++)
				{
					m_pHeightMaps[(m_height * j) + i].texture.x = tuCoordinate;
					m_pHeightMaps[(m_height * j) + i].texture.y = tvCoordinate;

					tuCoordinate += incrementValue;
					tuCount++;

					if (tuCount == incrementCount)
					{
						tuCoordinate = 0.0f;
						tuCount = 0;
					}
				}

				tvCoordinate -= incrementValue;
				tvCount++;

				if (tvCount == incrementCount)
				{
					tvCoordinate = 1.0f;
					tvCount = 0;
				}
			}
		}

		void CTerrain::SetVertex(int j, int i, float tu, float tv)
		{
			m_pVertices[i].position = m_pHeightMaps[j].position;
			m_pVertices[i].normal = m_pHeightMaps[j].normal;
			m_pVertices[i].texture = Vector2(tu, tv);
			m_pIndices[i] = i;
		}
	}
}