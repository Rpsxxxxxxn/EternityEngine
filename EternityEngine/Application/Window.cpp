#include "Window.h"

namespace Eternity
{
	namespace Application
	{
		// デストラクタ
		CWindow::~CWindow()
		{
		}

		// 生成処理
		void CWindow::Create(std::string name, UINT width, UINT height)
		{
			SetSettings(name, width, height);
			FindApplication();
			WindowRegister();
			WindowCreate();
		}

		// ループ処理
		bool CWindow::IsLoop()
		{
			if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&m_msg);

				DispatchMessage(&m_msg);
			}

			if (m_msg.message != WM_QUIT)
			{
				return true;
			}

			return false;
		}

		// 起動中のアプリケーションを探す
		void CWindow::FindApplication()
		{
			if (FindWindow((LPCSTR)m_className.c_str(), (LPCSTR)m_windowName.c_str()) != NULL)
			{
				exit(EOF);
			}
		}

		// ウィンドウハンドル
		HWND CWindow::GetHWND() const
		{
			return m_hWnd;
		}

		// インスタンスアプリケーション
		HINSTANCE CWindow::GetInstApp()
		{
			return m_hInst;
		}

		// ウィンドウ設定
		void CWindow::SetSettings(std::string name, UINT width, UINT height)
		{
			m_className = "3D_Game";
			m_windowName = name;
			m_width = width;
			m_height = height;
		}

		// ウィンドウの登録
		void CWindow::WindowRegister()
		{
			m_hInst = GetModuleHandle(NULL);

			//ウィンドウクラス
			WNDCLASS wc;
			wc.style = CS_VREDRAW | CS_HREDRAW;
			wc.hInstance = m_hInst;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = NULL;
			wc.lpszMenuName = NULL;
			wc.lpszClassName = (LPCSTR)m_className.c_str();
			wc.lpfnWndProc = WindowProc;

			//ウィンドウ登録
			if (!RegisterClass(&wc))
			{
				MessageBox(NULL, "ウィンドウ生成に失敗", "エラー", MB_OK);
			}
		}

		// ウィンドウの生成
		void CWindow::WindowCreate()
		{
			//ウィンドウ中央設定
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			RECT rect = { 0, 0, (LONG)m_width, (LONG)m_height };
			AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU, false);
			int windowWidth = rect.right - rect.left;
			int windowHeight = rect.bottom - rect.top;
			int windowX = (screenWidth - windowWidth) / 2;
			int windowY = (screenHeight - windowHeight) / 2;

			//ウィンドウ生成
			m_hWnd = CreateWindow(
				(LPCSTR)m_className.c_str(), (LPCSTR)m_windowName.c_str(),
				WS_CAPTION | WS_SYSMENU, windowX, windowY,
				windowWidth, windowHeight, NULL, NULL,
				m_hInst, NULL
			);

			//生成失敗時
			if (!m_hWnd)
			{
				MessageBox(NULL, "HWNDない", "エラー", MB_OK);
			}

			//ウィンドウの表示
			ShowWindow(m_hWnd, SW_SHOW);
			UpdateWindow(m_hWnd);
		}

		// プロシージャ
		LRESULT __stdcall CWindow::WindowProc(
			HWND hWnd,
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam
		)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

			switch (uMsg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}

			return 0L;
		}

	}
}