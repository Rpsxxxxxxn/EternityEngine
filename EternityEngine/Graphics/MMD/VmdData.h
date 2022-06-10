#pragma once

#include "../../Includer.h"
#include "../../Resources/Texture/WICTexture.h"
#include "../../Utility/Memory.h"
#include "MmdData.h"

namespace Eternity
{
	namespace Graphics
	{
		class CVmdData
		{
		public:
			CVmdData();
			~CVmdData();
			void ReadFile(string path);

			vector<VmdMotion> m_motions;
			vector<VmdSkin> m_skins;
			vector<VmdCamera> m_cameras;
			vector<VmdLight> m_lights;
			vector<VmdSelfShadow> m_shadows;
		private:
			void ReadHeader(ifstream* pIn);
			void ReadMotion(ifstream* pIn);
			void ReadSkin(ifstream* pIn);
			void ReadCamera(ifstream* pIn);
			void ReadLight(ifstream* pIn);
			void ReadShadow(ifstream* pIn);

			VmdHeader m_header;
			DWORD m_motionCount;
			DWORD m_skinCount;
			DWORD m_cameraCount;
			DWORD m_lightCount;
			DWORD m_selfShadowCount;
		};
	}
}