#include "Application.h"

namespace Eternity
{
	namespace Application
	{
		CApplication::CApplication()
			: m_pWindow(nullptr)
		{
		}

		CApplication::~CApplication()
		{
			Utility::CSingletonFinalizer::Finalize();
		}

		void CApplication::Initialize(std::string name, UINT width, UINT height, bool isWindow)
		{
			m_pWindow = make_unique<CWindow>();
			m_pWindow->Create(name, width, height);
			auto hwnd = m_pWindow->GetHWND();

			CDirectX::GetInstance().Create(hwnd);
			CShaderManager::GetInstance().Create();
			CGameObjectProvider::GetInstance().Initialize();
			CInput::GetInstance().Initialize(hwnd);
			CGamePad::GetInstance().Initialize(hwnd);
			CMouse::GetInstance().Initialize(hwnd);
			CGUIEditor::GetInstance().Create(hwnd);
			CGameRun::GetInstance().Initialize();
		}

		void CApplication::MainLoop()
		{
			while (m_pWindow->IsLoop())
			{
				Update();
				Draw();
			}
		}

		void CApplication::Update()
		{
			CGUIEditor::GetInstance().BeginPath();
			CTimer::GetInstance().Update();
			CInput::GetInstance().Update();
			CGamePad::GetInstance().Update();
			CMouse::GetInstance().Update();
			CGameObjectProvider::GetInstance().Update();
			CShaderManager::GetInstance().Update();
		}

		void CApplication::Draw()
		{
			CDirectX::GetInstance().BeginRender(0.0f, 0.0f, 0.0f, 1.0f);
			CShadowRenderProvider::GetInstance().Draw();
			CDirectX::GetInstance().ResetBackBufferTarget();
			CDirectX::GetInstance().ResetViewport();
			CRenderProvider::GetInstance().Draw();
			CGUIEditor::GetInstance().ClosePath();
			CDirectX::GetInstance().CloseRender();
		}
	}
}