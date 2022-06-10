#pragma once

#include "../Includer.h"
#include "../Utility/UtilityBundle.h"
#include "../Graphics/DirectX.h"
#include "../Graphics/Shader/ShaderManager.h"
#include "../Graphics/Render/RenderTexture.h"

namespace Eternity
{
	namespace Component
	{
		class CMeshRenderer;
	}

	namespace Provider
	{
		using namespace Graphics;
		using namespace Component;
		using namespace Utility;

		class CShadowRenderProvider : public CSingleton<CShadowRenderProvider>
		{
		public:
			CShadowRenderProvider() {};
			~CShadowRenderProvider();
			void Register(CMeshRenderer*);
			void Draw();
		private:
			void DrawTerrain();
			void DrawMesh();
			void DrawSkinMesh();
			void DrawBillboard();

			list<CMeshRenderer*> m_meshRenderer;
			shared_ptr<CRenderTexture> m_shadowTexture;
		};
	}
}