#pragma once

#include "MeshRender.h"

namespace Eternity
{
	namespace Component
	{
		class CMeshRenderer3D : public CMeshRenderer
		{
		public:
			CMeshRenderer3D(GameObject::IGameObject&);
			~CMeshRenderer3D();
			void Attach();
			void Initialize();
			void Draw();
		};
	}
}