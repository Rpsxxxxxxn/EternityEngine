#include "Window.h"

namespace Eternity
{
	namespace Application
	{
		// �f�X�g���N�^
		CWindow::~CWindow()
		{
		}

		// ��������
		void CWindow::Create(std::string name, UINT width, UINT height)
		{
			SetSettings(name, width, height);
			FindApplication();
			WindowRegister();
			WindowCreate();
		}

		// ���[�v����
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

		// �N�����̃A�v���P�[�V������T��
		void CWindow::FindApplication()
		{
			if (FindWindow((LPCSTR)m_className.c_str(), (LPCSTR)m_windowName.c_str()) != NULL)
			{
				exit(EOF);
			}
		}

		// �E�B���h�E�n���h��
		HWND CWindow::GetHWND() const
		{
			return m_hWnd;
		}

		// �C���X�^���X�A�v���P�[�V����
		HINSTANCE CWindow::GetInstApp()
		{
			return m_hInst;
		}

		// �E�B���h�E�ݒ�
		void CWindow::SetSettings(std::string name, UINT width, UINT height)
		{
			m_className = "3D_Game";
			m_windowName = name;
			m_width = width;
			m_height = height;
		}

		// �E�B���h�E�̓o�^
		void CWindow::WindowRegister()
		{
			m_hInst = GetModuleHandle(NULL);

			//�E�B���h�E�N���X
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

			//�E�B���h�E�o�^
			if (!RegisterClass(&wc))
			{
				MessageBox(NULL, "�E�B���h�E�����Ɏ��s", "�G���[", MB_OK);
			}
		}

		// �E�B���h�E�̐���
		void CWindow::WindowCreate()
		{
			//�E�B���h�E�����ݒ�
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			RECT rect = { 0, 0, (LONG)m_width, (LONG)m_height };
			AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU, false);
			int windowWidth = rect.right - rect.left;
			int windowHeight = rect.bottom - rect.top;
			int windowX = (screenWidth - windowWidth) / 2;
			int windowY = (screenHeight - windowHeight) / 2;

			//�E�B���h�E����
			m_hWnd = CreateWindow(
				(LPCSTR)m_className.c_str(), (LPCSTR)m_windowName.c_str(),
				WS_CAPTION | WS_SYSMENU, windowX, windowY,
				windowWidth, windowHeight, NULL, NULL,
				m_hInst, NULL
			);

			//�������s��
			if (!m_hWnd)
			{
				MessageBox(NULL, "HWND�Ȃ�", "�G���[", MB_OK);
			}

			//�E�B���h�E�̕\��
			ShowWindow(m_hWnd, SW_SHOW);
			UpdateWindow(m_hWnd);
		}

		// �v���V�[�W��
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