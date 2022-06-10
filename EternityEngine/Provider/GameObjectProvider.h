#pragma once

#include "../Includer.h"
#include "../Utility/UtilityBundle.h"
#include "../Graphics/DirectX.h"
#include "../Graphics/Shader/ShaderManager.h"
#include "../Graphics/Render/RenderTexture.h"

namespace Eternity
{
	namespace GameObject
	{
		class IGameObject;
	}

	namespace Provider
	{
		using namespace Graphics;
		using namespace GameObject;
		using namespace Utility;

		class CGameObjectProvider
			: public CSingleton<CGameObjectProvider>
		{
			vector<IGameObject*> m_objects;
			shared_ptr<CRenderTexture> m_shadowTexture;
		public:
			CGameObjectProvider();
			void Register(IGameObject*);
			void Initialize();
			void Update();
			void ShadowMeshDraw();
			void MeshDraw();

			vector<IGameObject*>* GetObjectList();
			IGameObject* GetGameObject(const UINT index);
		};
	}
}

#include "GameObjectProvider.h"