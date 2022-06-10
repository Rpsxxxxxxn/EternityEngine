#include "SkinMeshShader.h"

namespace Eternity
{
	namespace Graphics
	{
		CSkinMeshShader::CSkinMeshShader()
		{
			Create(
				"Assets/Shader/default_shader_skin_vs.hlsl",
				"Assets/Shader/default_shader_skin_ps.hlsl");
		}

		CSkinMeshShader::~CSkinMeshShader()
		{
		}
	}
}