#include "VmdData.h"

namespace Eternity
{
	namespace Graphics
	{
		CVmdData::CVmdData()
			: m_motionCount(0)
			, m_skinCount(0)
			, m_cameraCount(0)
			, m_lightCount(0)
			, m_selfShadowCount(0)
		{
		}

		CVmdData::~CVmdData()
		{
			m_motions.clear();
			m_skins.clear();
			m_cameras.clear();
			m_lights.clear();
			m_shadows.clear();
		}

		void CVmdData::ReadFile(string path)
		{
			ifstream ifs(path, ios::binary);

			ReadHeader(&ifs);
			ReadMotion(&ifs);
			ReadSkin(&ifs);
			ReadCamera(&ifs);
			ReadLight(&ifs);
			ReadShadow(&ifs);

			ifs.close();
		}

		void CVmdData::ReadHeader(ifstream* pIn)
		{
			pIn->read(m_header.header, sizeof(char) * 30);
			pIn->read(m_header.modelName, sizeof(char) * 20);
		}

		void CVmdData::ReadMotion(ifstream* pIn)
		{
			pIn->read((char*)&m_motionCount, sizeof(DWORD));

			m_motions.resize(m_motionCount);

			for (DWORD i = 0; i < m_motionCount; i++)
			{
				pIn->read(m_motions[i].boneName, sizeof(char) * 15);
				pIn->read((char*)&m_motions[i].frameNo, sizeof(DWORD));
				pIn->read((char*)&m_motions[i].location, sizeof(float) * 3);
				pIn->read((char*)&m_motions[i].rotation, sizeof(float) * 4);
				pIn->read((char*)&m_motions[i].interpolation, sizeof(BYTE) * 64);
			}
		}

		void CVmdData::ReadSkin(ifstream* pIn)
		{
			pIn->read((char*)&m_skinCount, sizeof(DWORD));

			m_skins.resize(m_skinCount);

			for (DWORD i = 0; i < m_skinCount; i++)
			{
				pIn->read(m_skins[i].skinName, sizeof(char) * 15);
				pIn->read((char*)&m_skins[i].flameNo, sizeof(DWORD));
				pIn->read((char*)&m_skins[i].weight, sizeof(float));
			}
		}

		void CVmdData::ReadCamera(ifstream* pIn)
		{
			pIn->read((char*)&m_cameraCount, sizeof(DWORD));

			m_cameras.resize(m_cameraCount);

			for (DWORD i = 0; i < m_cameraCount; i++)
			{
				pIn->read((char*)&m_cameras[i].flameNo, sizeof(DWORD));
				pIn->read((char*)&m_cameras[i].length, sizeof(float));
				pIn->read((char*)&m_cameras[i].location, sizeof(float) * 3);
				pIn->read((char*)&m_cameras[i].rotation, sizeof(float) * 3);
				pIn->read((char*)&m_cameras[i].interpolation, sizeof(BYTE));
				pIn->read((char*)&m_cameras[i].viewingAngle, sizeof(DWORD));
				pIn->read((char*)&m_cameras[i].perspective, sizeof(BYTE));
			}
		}

		void CVmdData::ReadLight(ifstream* pIn)
		{
			pIn->read((char*)&m_lightCount, sizeof(DWORD));

			m_lights.resize(m_lightCount);

			for (DWORD i = 0; i < m_lightCount; i++)
			{
				pIn->read((char*)&m_lights[i].flameNo, sizeof(DWORD));
				pIn->read((char*)&m_lights[i].rgb, sizeof(float) * 3);
				pIn->read((char*)&m_lights[i].location, sizeof(float) * 3);
			}
		}

		void CVmdData::ReadShadow(ifstream* pIn)
		{
			pIn->read((char*)&m_selfShadowCount, sizeof(DWORD));

			m_shadows.resize(m_selfShadowCount);

			for (DWORD i = 0; i < m_selfShadowCount; i++)
			{
				pIn->read((char*)&m_shadows[i].flameNo, sizeof(DWORD));
				pIn->read((char*)&m_shadows[i].mode, sizeof(BYTE));
				pIn->read((char*)&m_shadows[i].distance, sizeof(float));
			}
		}
	}
}