#include "NormalShader.h"

namespace Eternity
{
	namespace Graphics
	{
		// �R���X�g���N�^
		CNormalShader::CNormalShader()
			: IShader()
		{
			Create(
				"Assets/Shader/default_shader_vs.hlsl",
				"Assets/Shader/default_shader_ps.hlsl");
		}

		// �f�X�g���N�^
		CNormalShader::~CNormalShader()
		{
		}
	}
}