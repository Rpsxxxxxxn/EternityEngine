#pragma once

#include "Window.h"
#include "../Graphics/DirectX.h"
#include "../Provider/GameObjectProvider.h"
#include "../Provider/RenderProvider.h"
#include "../Provider/ShadowRenderProvider.h"
#include "../Graphics/Shader/ShaderManager.h"
#include "../Editors/GUIEditor.h"
#include "../GameRun/GameRun.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Application
	{
		using namespace Graphics;
		using namespace Provider;
		using namespace Utility;
		using namespace Editor;
		using namespace Game;

		class CApplication final
		{
		public:
			CApplication();
			~CApplication();
			void Initialize(std::string, UINT, UINT, bool);
			void MainLoop();
		private:
			void Update();
			void Draw();

			unique_ptr<CWindow> m_pWindow;
		};
	};
}