#include "TerrainShader.h"

namespace Eternity
{
	namespace Graphics
	{
		CTerrainShader::CTerrainShader()
		{
			Create(
				"Assets/Shader/terrain_shader_vs.hlsl",
				"Assets/Shader/terrain_shader_ps.hlsl");
		}

		CTerrainShader::~CTerrainShader()
		{
		}
	}
}