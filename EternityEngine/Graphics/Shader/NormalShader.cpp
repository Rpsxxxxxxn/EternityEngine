#include "NormalShader.h"

namespace Eternity
{
	namespace Graphics
	{
		// コンストラクタ
		CNormalShader::CNormalShader()
			: IShader()
		{
			Create(
				"Assets/Shader/default_shader_vs.hlsl",
				"Assets/Shader/default_shader_ps.hlsl");
		}

		// デストラクタ
		CNormalShader::~CNormalShader()
		{
		}
	}
}