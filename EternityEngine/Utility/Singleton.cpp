#include "Singleton.h"

namespace Eternity
{
	namespace Utility
	{
		std::vector<CSingletonFinalizer::
			FinalizerFunc>CSingletonFinalizer::m_finalizer = {};

		void CSingletonFinalizer::AddFinalizer(FinalizerFunc func)
		{
			m_finalizer.push_back(func);
		}

		void CSingletonFinalizer::Finalize()
		{
			std::reverse(m_finalizer.begin(), m_finalizer.end());
			for (auto& w : m_finalizer)
			{
				w();
			}
		}
	}
}