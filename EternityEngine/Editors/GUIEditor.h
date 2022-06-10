#pragma once

#include "../Includer.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Editor
	{
		class CGUIEditor : public Utility::CSingleton<CGUIEditor>
		{
		public:
			CGUIEditor();
			~CGUIEditor();
			void Create(HWND hwnd);
			void BeginPath();
			void ClosePath();
		};
	}
}