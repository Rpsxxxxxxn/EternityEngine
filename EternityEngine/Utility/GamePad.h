#pragma once

#include "../Includer.h"
#include "Singleton.h"
#include "Memory.h"

namespace Eternity
{
	namespace Utility
	{
		class CGamePad
			: public CSingleton<CGamePad>
		{
			LPDIRECTINPUT8 m_pInput;
			LPDIRECTINPUTDEVICE8 m_pInputDevice;
			DIDEVCAPS m_devCaps;

			DIJOYSTATE m_oldJS;
			DIJOYSTATE m_newJS;
		public:
			CGamePad();
			~CGamePad();
			void Initialize(HWND);
			void Update();

			bool IsPressed(const BYTE);
			bool IsDown(const BYTE);
			bool IsUp(const BYTE);
		private:
			void CreateDevice();
			void SetDataFormat();
			void SetCooperativeLevel(HWND);
			void SetCapabilities();
			void SetEnumObject();
			void SetPooling();
			void SetDeviceState();
			static bool __stdcall EnumJoysticksCallback(const DIDEVICEINSTANCE*, void*);
			static bool __stdcall EnumAxesCallback(const DIDEVICEOBJECTINSTANCE*, void*);
		};
	}
}