#pragma once

#include "../IComponent.h"

namespace Eternity
{
	namespace Component
	{
		using namespace GameObject;

		class CMeshRenderer : public IComponent
		{
		public:
			CMeshRenderer(IGameObject&);
			virtual ~CMeshRenderer() {};
			virtual void Initialize() = 0;
			virtual void Draw() = 0;
		};
	}
}