#pragma once

#include "../Includer.h"

namespace Eternity
{
	namespace Utility
	{
		template <typename T>
		void SafeDelete(T*& p);

		template <typename T>
		void SafeDeleteArray(T*& p);

		template <typename T>
		void SafeRelease(T*& p);
	}
}
#include "Memory.inl"