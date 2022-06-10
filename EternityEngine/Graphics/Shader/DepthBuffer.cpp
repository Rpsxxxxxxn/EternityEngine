#include "DepthBuffer.h"

namespace Eternity
{
	namespace Graphics
	{
		CDepthBuffer::CDepthBuffer()
		{
			Create(
				"Assets/Shader/depth_shader_vs.hlsl",
				"Assets/Shader/depth_shader_ps.hlsl");
		}

		CDepthBuffer::~CDepthBuffer()
		{

		}
	}
}