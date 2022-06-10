#pragma once

#include "IShader.h"

namespace Eternity
{
	namespace Graphics
	{
		class CDepthBuffer : public IShader
		{
		public:
			CDepthBuffer();
			~CDepthBuffer();
		};
	}
}