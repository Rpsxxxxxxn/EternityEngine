#pragma once

#include "../../Includer.h"
#include "../../Utility/Memory.h"

namespace Eternity
{
	namespace Graphics
	{
		struct BillboardVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector4 color;
			Vector2 texture;
		};

		class CBillboard
		{
		public:
			CBillboard();
			~CBillboard();
			void Create();

			ID3D11Buffer* GetVertexBuffer() const;
			int GetVertexCount() const;
		private:
			ID3D11Buffer* m_pVertexBuffer;
			int m_vertexCount;
		};
	}
}