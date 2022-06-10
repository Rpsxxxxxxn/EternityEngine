#pragma once

#include "../../Includer.h"

namespace Eternity
{
	namespace Graphics
	{
		class CFbxMotionController
		{
		public:
			CFbxMotionController();
			~CFbxMotionController();
			void Initialize(FbxScene* pScene);
			void UpdateBoneMatrix(FbxNode* pNode, FbxMesh* pMesh);
			void AdvancedTime();
		private:
			FbxNode* m_pNode;
			FbxArray<FbxString*> m_animStack;
			uint32_t m_animStackNum;
			FbxTime m_frameTime;
			FbxTime m_timeCount;
			FbxTime m_start;
			FbxTime m_stop;
		};
	}
}