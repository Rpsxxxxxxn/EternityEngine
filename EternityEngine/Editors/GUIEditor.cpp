#include "GUIEditor.h"
#include "../Graphics/DirectX.h"

namespace Eternity
{
	namespace Editor
	{
		CGUIEditor::CGUIEditor()
		{
		}

		CGUIEditor::~CGUIEditor()
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
		}

		void CGUIEditor::Create(HWND hwnd)
		{
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromFileTTF(
				"Includes/ImGui/msgothic.ttc",
				15.0f, nullptr,
				io.Fonts->GetGlyphRangesJapanese());
			ImGui_ImplWin32_Init(hwnd);

			auto device = Graphics::CDirectX::GetInstance().GetDevice();
			auto context = Graphics::CDirectX::GetInstance().GetContext();
			ImGui_ImplDX11_Init(device, context);
		}

		void CGUIEditor::BeginPath()
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		}

		void CGUIEditor::ClosePath()
		{
			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}
}
