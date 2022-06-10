#pragma once

#include "./IGameObject.h"

namespace Eternity
{
	namespace GameObject
	{
		class CEmptyObject
			: public IGameObject
		{
		public:
			CEmptyObject();
			~CEmptyObject();
			void Initialize();
			void Update();
		};
	}
}