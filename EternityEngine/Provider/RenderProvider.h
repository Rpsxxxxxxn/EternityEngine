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

		enum RenderType
		{
			DEFAULT,
			SKIN_MESH,
			TERRAIN,
			TYPE_MAX,
		};

		class CRenderProvider : public CSingleton<CRenderProvider>
		{
		public:
			CRenderProvider() {};
			~CRenderProvider();
			void Register(CMeshRenderer*, RenderType);
			void Draw();
		private:
			void DrawTerrain();
			void DrawMesh();
			void DrawSkinMesh();
			void DrawBillboard();

			list<CMeshRenderer*> m_meshRenderer[TYPE_MAX];
			shared_ptr<CRenderTexture> m_shadowTexture;
		};
	}
}