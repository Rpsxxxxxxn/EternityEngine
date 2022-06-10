#pragma once

#include "../Includer.h"
#include "../Graphics/Terrain/QuadTree.h"
#include "../Graphics/Fbx/FbxData.h"
#include "../Graphics/MMD/PmdData.h"
#include "../Graphics/MMD/VmdData.h"
#include "../GameObject/DirectionLight.h"
#include "../GameObject/PointLight.h"
#include "../GameObject/SpotLight.h"
#include "../GameObject/EmptyObject.h"
#include "../Components/Behavior/Camera.h"
#include "../Components/Rigidbody/Rigidbody.h"
#include "../Components/Renderer/MeshRender3DSkin.h"
#include "../Components/Renderer/MeshRenderTerrain.h"
#include "../Utility/UtilityBundle.h"

namespace Eternity
{
	namespace Game
	{
		using namespace GameObject;

		class CGameRun
			: public Utility::CSingleton<CGameRun>
		{
			CPmdData m_modelData;
			CTerrain m_terrainData;
			CDirectionLight m_light;
			CEmptyObject m_terrain;
			CEmptyObject m_camera;
			CEmptyObject m_model;
		public:
			CGameRun();
			~CGameRun();
			void Initialize();
		};
	}
}