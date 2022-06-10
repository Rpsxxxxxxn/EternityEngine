#pragma once

// インクルード
#include "../Includer.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Application
	{
		class CWindow final
		{
		public:
			CWindow() = default;
			~CWindow();
			void Create(std::string, UINT, UINT);
			bool IsLoop();
			void FindApplication();
			HWND GetHWND() const;
			HINSTANCE GetInstApp();
		private:
			void SetSettings(std::string, UINT, UINT);
			void WindowRegister();
			void WindowCreate();
			static LRESULT __stdcall WindowProc(HWND, UINT, WPARAM, LPARAM);

			HWND		m_hWnd;
			MSG			m_msg;
			HINSTANCE	m_hInst;
			std::string m_className;
			std::string m_windowName;
			UINT		m_width;
			UINT		m_height;
		};
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);