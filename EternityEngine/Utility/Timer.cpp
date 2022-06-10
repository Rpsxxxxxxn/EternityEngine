#include "Timer.h"

namespace Eternity
{
	namespace Utility
	{
		float CTimer::DeltaTime = 0.0f;
		float CTimer::TimeScale = 0.001f;

		CTimer::CTimer()
		{
			m_startClock = std::chrono::system_clock::now();
		}

		void CTimer::Update()
		{
			m_endClock = std::chrono::system_clock::now();

			DeltaTime =
				static_cast<float>(
					std::chrono::duration_cast<std::chrono::milliseconds>
					(m_endClock - m_startClock).count() * TimeScale);

			m_startClock = std::chrono::system_clock::now();
		}
	}
}