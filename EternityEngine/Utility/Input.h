#pragma once

#include "../Includer.h"
#include "Singleton.h"
#include "Memory.h"

namespace Eternity
{
	namespace Utility
	{
		class CInput
			: public CSingleton<CInput>
		{
			LPDIRECTINPUT8 m_pInput;
			LPDIRECTINPUTDEVICE8 m_pInputDevice;
			BYTE m_keys[256];
			BYTE m_olds[256];
		public:
			CInput();
			~CInput();
			void Initialize(HWND);
			void Update();

			bool IsPressed(const BYTE);
			bool IsDown(const BYTE);
			bool IsUp(const BYTE);
		};
	}
}