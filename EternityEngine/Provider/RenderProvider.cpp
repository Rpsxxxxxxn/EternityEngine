#include "RenderProvider.h"
#include "../Components/Renderer/MeshRender.h"
#include "../Components/Renderer/MeshRender3D.h"
#include "../Components/Renderer/MeshRender3DSkin.h"
#include "../Components/Renderer/MeshRenderTerrain.h"
#include "../Components/Transform/Transform.h"
#include "../GameObject/IGameObject.h"

namespace Eternity
{
	namespace Provider
	{
		CRenderProvider::~CRenderProvider()
		{
			for (UINT i = 0; i < RenderType::TYPE_MAX; i++)
			{
				m_meshRenderer[i].clear();
			}
		}

		void CRenderProvider::Register(CMeshRenderer* pData, RenderType type)
		{
			m_meshRenderer[type].push_back(pData);
		}

		void CRenderProvider::Draw()
		{
			// �n�`�`��
			DrawTerrain();

			// ���b�V���`��
			DrawMesh();

			// �X�L�����b�V���`��
			DrawSkinMesh();
		}

		// �n�`�`�揈��
		void CRenderProvider::DrawTerrain()
		{
			auto& meshRenderer = m_meshRenderer[TERRAIN];

			for (auto iterator = meshRenderer.begin(); iterator != meshRenderer.end(); ++iterator)
			{
				auto transform = (*iterator)->GetGameObject()->GetComponent<Component::Transform>();
				auto terrain = CShaderManager::GetInstance().GetShader<CTerrainShader>();

				(terrain)->SetWorldMatrix(transform->GetTransform());
				(terrain)->CommitChanges();
				(terrain)->SetShader();

				(*iterator)->Draw();
			}
		}

		// �Œ胁�b�V���`�揈��
		void CRenderProvider::DrawMesh()
		{
			auto& meshRenderer = m_meshRenderer[DEFAULT];

			for (auto iterator = meshRenderer.begin(); iterator != meshRenderer.end(); ++iterator)
			{
				auto transform = (*iterator)->GetGameObject()->GetComponent<Component::Transform>();
				auto meshShader = CShaderManager::GetInstance().GetShader<CNormalShader>();

				(meshShader)->SetWorldMatrix(transform->GetTransform());
				(meshShader)->CommitChanges();
				(meshShader)->SetShader();

				(*iterator)->Draw();
			}
		}

		// �X�L�����b�V���`�揈��
		void CRenderProvider::DrawSkinMesh()
		{
			auto& meshRenderer = m_meshRenderer[SKIN_MESH];

			for (auto iterator = meshRenderer.begin(); iterator != meshRenderer.end(); ++iterator)
			{
				auto transform = (*iterator)->GetGameObject()->GetComponent<Component::Transform>();
				auto skinShader = CShaderManager::GetInstance().GetShader<CNormalShader>();

				(skinShader)->SetWorldMatrix(transform->GetTransform());
				(skinShader)->CommitChanges();
				(skinShader)->SetShader();

				(*iterator)->Draw();
			}
		}

		// �r���{�[�h�`�揈��
		void CRenderProvider::DrawBillboard()
		{
		}
	}
}