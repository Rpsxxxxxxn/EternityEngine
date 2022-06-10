#include "GameRun.h"

namespace Eternity
{
	namespace Game
	{
		CGameRun::CGameRun()
		{
		}

		CGameRun::~CGameRun()
		{
		}

		void CGameRun::Initialize()
		{
			m_light.Initialize();
			m_terrainData.Create();;
			m_modelData.ReadFile("Assets/Model/nyako.pmd");

			m_camera.AddComponent<Component::CCamera>();

			auto terrain = m_terrain.AddComponent<Component::CMeshRendererTerrain>();
			terrain->Attach(&m_terrainData);
			terrain->Initialize();

			auto model = m_model.AddComponent<Component::CMeshRenderer3DSkin>();
			model->Attach(&m_modelData);
			model->Initialize();
		}
	}
}