#pragma once

#include "../../Includer.h"
#include "PmdData.h"
#include "VmdData.h"

namespace Eternity
{
	namespace Graphics
	{
		struct KeyFrame
		{
			string boneName;
			DWORD frameNo;
			Vector3 position;
			Quaternion rotation;
			Vector2 interpolationX[2];
			Vector2 interpolationY[2];
			Vector2 interpolationZ[2];
			Vector2 interpolationW[2];
			bool operator < (const KeyFrame& k) const
			{
				return frameNo < k.frameNo;
			}
		};

		class CVmdController
		{
		public:
			static const int FRAME_RATE;
			static const int VMD_FRAME_RATE;

			CVmdController();
			void ReadFile(string path, vector<PmdBoneEx>* pBones);
			void UpdateBoneMatrix();
			void AdvanceTime();
		private:
			int m_time;

			vector<PmdBoneEx>* m_bones;
			vector<Quaternion> m_boneRotation;
			vector<Vector3> m_bonePosition;
			vector<CVmdData*> m_vmdList;

			vector<list<KeyFrame>> m_keyFrames;
			vector<list<KeyFrame>::iterator> itrKeyFrames;
		};
	}
}