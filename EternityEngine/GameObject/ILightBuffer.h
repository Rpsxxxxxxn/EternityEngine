#pragma once

#include "../Includer.h"

namespace Eternity
{
	namespace GameObject
	{
		// 定数バッファ向けライトパラメータ
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

		// 別格納用ライトパラメータ
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