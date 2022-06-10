#pragma once

#include "../Includer.h"

namespace Eternity
{
	namespace GameObject
	{
		// �萔�o�b�t�@�������C�g�p�����[�^
		struct LightBuffer
		{
			XMVECTOR position;
			XMVECTOR direction;
			XMVECTOR ambient;
			XMVECTOR diffuse;
			XMMATRIX lightView;
			XMMATRIX lightProj;
			float range;
			float innerCone;
			float outerCone;
		};

		// �ʊi�[�p���C�g�p�����[�^
		struct LightParams
		{
			Vector4 ambient;
			Vector4 diffuse;
			Matrix lightView;
			Matrix lightProj;
			float range;
			float innerCone;
			float outerCone;
		};
	}
}