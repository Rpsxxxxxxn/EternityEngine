#pragma once

#include "MeshRender.h"
#include "../../Graphics/Fbx/FbxData.h"
#include "../../Graphics/MMD/PmdData.h"
#include "../../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Component
	{
		class CMeshRenderer3DSkin : public CMeshRenderer
		{
		public:
			CMeshRenderer3DSkin(GameObject::IGameObject&);
			~CMeshRenderer3DSkin();
			void Attach(Graphics::CPmdData* pData);
			void Initialize();
			void Draw();
		private:
			void DrawMesh(const UINT index);

			Graphics::CPmdData* m_pData;
			int m_startIndex;
		};
	}
}