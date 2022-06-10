#pragma once

#include "../../Includer.h"
#include "../../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Graphics
	{
		struct DomeVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector4 color;
			Vector2 texture;
		};

		class CSkyDome
		{
		public:
			CSkyDome();
			~CSkyDome();
			void Create();
		private:
			void CreateVertex();
			void CreateBuffer();

			DomeVertex* m_pVertices;
			ID3D11Buffer* m_pVertexBuffer;
			ID3D11Buffer* m_pIndexBuffer;
			Vector4 m_apexColor;
			Vector4 m_centerColor;
			int m_vertexCount;
			int m_indexCount;
		};
	}
}