#include "MeshRender3D.h"
#include "../../Provider/RenderProvider.h"

namespace Eternity
{
	namespace Component
	{
		CMeshRenderer3D::CMeshRenderer3D(GameObject::IGameObject& owner)
			: CMeshRenderer(owner)
		{
			Provider::CRenderProvider::GetInstance().Register(this, Provider::DEFAULT);
		}

		CMeshRenderer3D::~CMeshRenderer3D()
		{
		}

		void CMeshRenderer3D::Attach()
		{
		}

		void CMeshRenderer3D::Initialize()
		{
		}

		void CMeshRenderer3D::Draw()
		{
		}
	}
}