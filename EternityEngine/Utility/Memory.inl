#include "Memory.h"

namespace Eternity
{
	namespace Utility
	{
		template<typename T>
		inline void SafeDelete(T*& p)
		{
			if (p != nullptr)
			{
				delete (p);
				(p) = nullptr;
			}
		}

		template<typename T>
		inline void SafeDeleteArray(T*& p)
		{
			if (p != nullptr)
			{
				delete[](p);
				(p) = nullptr;
			}
		}

		template<typename T>
		inline void SafeRelease(T*& p)
		{
			if (p != nullptr)
			{
				(p)->Release();
				(p) = nullptr;
			}
		}
	}
}