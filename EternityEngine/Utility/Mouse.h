#pragma once

#include "../Includer.h"
#include "Singleton.h"
#include "Memory.h"

namespace Eternity
{
	namespace Utility
	{
		class CMouse
			: public CSingleton<CMouse>
		{
			LPDIRECTINPUT8 m_pInput;
			LPDIRECTINPUTDEVICE8 m_pInputDevice;

			DIMOUSESTATE m_oldMS;
			DIMOUSESTATE m_newMS;
		public:
			CMouse();
			~CMouse();
			void Initialize(HWND);
			void Update();

			// Getter
			bool IsPressed(const BYTE);
			bool IsDown(const BYTE);
			bool IsUp(const BYTE);
			POINT GetMouseMove();
			float GetMouseWheel();
		};
	}
}