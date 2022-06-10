#pragma once

#include "./IGameObject.h"

namespace Eternity
{
	namespace GameObject
	{
		class CParticles : public IGameObject
		{
		public:
			CParticles();
			~CParticles();
			void Initialize();
			void Update();
		};
	}
}