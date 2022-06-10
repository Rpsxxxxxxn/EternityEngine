#include "FbxMotionController.h"

namespace Eternity
{
	namespace Graphics
	{
		CFbxMotionController::CFbxMotionController()
		{
		}

		CFbxMotionController::~CFbxMotionController()
		{
		}

		void CFbxMotionController::Initialize(FbxScene* pScene)
		{
			pScene->FillAnimStackNameArray(m_animStack);
			FbxAnimStack* pAnimStack = pScene->FindMember<FbxAnimStack>(m_animStack[m_animStackNum]->Buffer());
			pScene->SetCurrentAnimationStack(pAnimStack);

			FbxTakeInfo* pTakeInfo = pScene->GetTakeInfo(*(m_animStack[m_animStackNum]));
			m_start = pTakeInfo->mLocalTimeSpan.GetStart();
			m_stop = pTakeInfo->mLocalTimeSpan.GetStop();
			m_frameTime.SetTime(0, 0, 0, 1, 0, pScene->GetGlobalSettings().GetTimeMode());
			m_timeCount = m_start;
		}

		void CFbxMotionController::UpdateBoneMatrix(FbxNode* pNode, FbxMesh* pMesh)
		{
			// ˆÚ“® - ‰ñ“] - Šg‘å
			FbxMatrix globalPosition = pNode->EvaluateGlobalTransform(m_timeCount);
			FbxVector4 t0 = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
			FbxVector4 r0 = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
			FbxVector4 s0 = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
			FbxAMatrix geometryOffset = FbxAMatrix(t0, r0, s0);

			// Še’¸“_
			FbxMatrix* pClusterDeformation = new FbxMatrix[pMesh->GetControlPointsCount()];
			memset(pClusterDeformation, 0, sizeof(FbxMatrix) * pMesh->GetControlPointsCount());

			FbxSkin* pSkinDeformer = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
			int clusterCount = pSkinDeformer->GetClusterCount();

			for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* pCluster = pSkinDeformer->GetCluster(clusterIndex);
				FbxMatrix vertexTransformMatrix;
				FbxAMatrix referenceGlobalInitPosition;
				FbxAMatrix clusterGlobalInitPosition;
				FbxMatrix clusterGlobalCurrentPosition;
				FbxMatrix clusterRelativeInitPosition;
				FbxMatrix clusterRelativeCurrentPositionInverse;
				pCluster->GetTransformMatrix(referenceGlobalInitPosition);
				referenceGlobalInitPosition *= geometryOffset;
				pCluster->GetTransformLinkMatrix(clusterGlobalInitPosition);
				clusterGlobalCurrentPosition = pCluster->GetLink()->EvaluateGlobalTransform(m_timeCount);
				clusterRelativeInitPosition = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;
				clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;
				vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;

				for (int i = 0; i < pCluster->GetControlPointIndicesCount(); i++) {
					int index = pCluster->GetControlPointIndices()[i];
					double weight = pCluster->GetControlPointWeights()[i];
					FbxMatrix influence = vertexTransformMatrix * weight;
					pClusterDeformation[index] += influence;
				}
			}
		}

		void CFbxMotionController::AdvancedTime()
		{
			m_timeCount += m_frameTime;

			if (m_timeCount > m_stop)
			{
				m_timeCount = m_start;
			}
		}
	}
}