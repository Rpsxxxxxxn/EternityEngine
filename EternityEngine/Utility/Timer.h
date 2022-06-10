#pragma once

// インクルード
#include "../Includer.h"
#include "Singleton.h"

namespace Eternity
{
	namespace Utility
	{
		class CTimer
			: public CSingleton<CTimer>
		{
		public:
			static float DeltaTime;
			static float TimeScale;

			CTimer();
			void Update();
		private:
			std::chrono::system_clock::time_point m_startClock;
			std::chrono::system_clock::time_point m_endClock;
		};
	}
}