#include "GameObjectProvider.h"
#include "../GameObject/IGameObject.h"
#include "../Components/IComponent.h"

namespace Eternity
{
	namespace Provider
	{
		const int SHADOW_MAP_SIZE = 5000;

		CGameObjectProvider::CGameObjectProvider()
			: m_shadowTexture(nullptr)
		{
		}

		// 登録処理
		void CGameObjectProvider::Register(IGameObject* pData)
		{
			m_objects.push_back(pData);
		}

		// シャドウマップテクスチャ用初期化処理
		void CGameObjectProvider::Initialize()
		{
			m_shadowTexture = make_unique<CRenderTexture>();
			m_shadowTexture->Create(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
		}

		// 更新処理
		void CGameObjectProvider::Update()
		{
			std::for_each(m_objects.begin(), m_objects.end(),
				[&](IGameObject* pEntity) { pEntity->FirstUpdate(); });

			std::for_each(m_objects.begin(), m_objects.end(),
				[&](IGameObject* pEntity) { pEntity->Update(); });

			std::for_each(m_objects.begin(), m_objects.end(),
				[&](IGameObject* pEntity) { pEntity->LateUpdate(); });
		}

		// オブジェクトリストの取得
		vector<IGameObject*>* CGameObjectProvider::GetObjectList()
		{
			return &m_objects;
		}

		IGameObject* CGameObjectProvider::GetGameObject(const UINT index)
		{
			if (index >= m_objects.size())
				return nullptr;

			return m_objects[index];
		}

		// シャドウ用メッシュ描画
		void CGameObjectProvider::ShadowMeshDraw()
		{
			m_shadowTexture->SetRenderTarget();
			m_shadowTexture->ClearRenderTarget();

			for (auto iterator = m_objects.begin(); iterator != m_objects.end(); iterator++)
			{
				auto shader = CShaderManager::GetInstance().GetShader<CDepthBuffer>();
				auto transform = (*iterator)->GetComponent<Component::Transform>();
				shader->SetWorldMatrix(transform->GetTransform());
				shader->CommitChanges();
				shader->SetShader();

				(*iterator)->Draw();
			}

			CDirectX::GetInstance().ResetBackBufferTarget();
			CDirectX::GetInstance().ResetViewport();

			m_shadowTexture->SetRenderResourceView();
		}

		// 通常描画処理
		void CGameObjectProvider::MeshDraw()
		{
			CDirectX::GetInstance().BeginRender(0.0f, 0.0f, 0.0f, 1.0f);

			for (auto iterator = m_objects.begin(); iterator != m_objects.end(); iterator++)
			{
				auto shader = CShaderManager::GetInstance().GetShader<CNormalShader>();
				auto transform = (*iterator)->GetComponent<Component::Transform>();
				shader->SetWorldMatrix(transform->GetTransform());
				shader->CommitChanges();
				shader->SetShader();

				(*iterator)->Draw();
			}
		}
	}
}