#include "VmdController.h"

namespace Eternity
{
	namespace Graphics
	{
		const int CVmdController::FRAME_RATE = 60;
		const int CVmdController::VMD_FRAME_RATE = 30;

		CVmdController::CVmdController()
		{
		}

		void CVmdController::ReadFile(string path, vector<PmdBoneEx>* pBones)
		{
			m_bones = pBones;

			ifstream ifs(path, ios::binary);

			// ヘッダーの読み込み
			VmdHeader header;
			ifs.read((char*)&header, sizeof(VmdHeader));

			// モーション数の読み取り
			ULONG numMotion;
			ifs.read((char*)&numMotion, sizeof(numMotion));

			// モーションデータの取得
			vector<VmdMotion> motions(numMotion);
			ifs.read((char*)&motions[0], sizeof(VmdMotion) * numMotion);

			ifs.close();

			m_keyFrames.resize(m_bones->size());
			for (UINT i = 0; i < motions.size(); ++i)
			{
				KeyFrame keyFrame;
				keyFrame.boneName = motions[i].boneName;
				keyFrame.frameNo = motions[i].frameNo;
				keyFrame.frameNo *= FRAME_RATE / VMD_FRAME_RATE;
				keyFrame.position = Vector3(motions[i].location[0], motions[i].location[1], motions[i].location[2]);
				keyFrame.rotation = Quaternion(motions[i].rotation[0], motions[i].rotation[1], motions[i].rotation[2], motions[i].rotation[3]);
				keyFrame.interpolationX[0] = Vector2(motions[i].interpolation[0], motions[i].interpolation[4]);
				keyFrame.interpolationX[1] = Vector2(motions[i].interpolation[8], motions[i].interpolation[12]);
				keyFrame.interpolationY[0] = Vector2(motions[i].interpolation[1], motions[i].interpolation[5]);
				keyFrame.interpolationY[1] = Vector2(motions[i].interpolation[9], motions[i].interpolation[13]);
				keyFrame.interpolationZ[0] = Vector2(motions[i].interpolation[2], motions[i].interpolation[6]);
				keyFrame.interpolationZ[1] = Vector2(motions[i].interpolation[10], motions[i].interpolation[14]);
				keyFrame.interpolationW[0] = Vector2(motions[i].interpolation[3], motions[i].interpolation[7]);
				keyFrame.interpolationW[1] = Vector2(motions[i].interpolation[11], motions[i].interpolation[15]);
				for (UINT j = 0; j < m_bones->size(); ++j)
				{
					if (keyFrame.boneName == (*m_bones)[j].name)
					{
						m_keyFrames[j].push_back(keyFrame);
						break;
					}
				}
			}

			for (UINT i = 0; i < m_bones->size(); ++i)
			{
				m_keyFrames[i].sort();
				itrKeyFrames.push_back(m_keyFrames[i].begin());
				m_boneRotation.push_back(Quaternion::Identity);
				m_bonePosition.push_back(Vector3::Zero);
			}

			UpdateBoneMatrix();
		}

		void CVmdController::UpdateBoneMatrix()
		{
			for (UINT i = 0; i < m_bones->size(); i++)
			{
				ULONG t0, t1;
				Quaternion q0, q1;
				Vector3 p0, p1;
				if (itrKeyFrames[i] != m_keyFrames[i].end())
				{
					t0 = (*itrKeyFrames[i]).frameNo;
					m_boneRotation[i] = q0 = (*itrKeyFrames[i]).rotation;
					m_bonePosition[i] = p0 = (*itrKeyFrames[i]).position;

					if (++itrKeyFrames[i] != m_keyFrames[i].end())
					{
						t1 = (*itrKeyFrames[i]).frameNo;
						q1 = (*itrKeyFrames[i]).rotation;
						p1 = (*itrKeyFrames[i]).position;

						float s = (float)(m_time - t0) / (float)(t1 - t0);
						m_boneRotation[i] = Quaternion::Slerp(q0, q1, s);
						m_bonePosition[i] = p0 + (p1 - p0) * s;
						if (m_time != t1)
						{
							--itrKeyFrames[i];
						}
					}
				}

				Matrix rotate = XMMatrixRotationQuaternion(m_boneRotation[i]);
				Matrix trans = XMMatrixTranslation(m_bonePosition[i].x, m_bonePosition[i].y, m_bonePosition[i].z);
				(*m_bones)[i].boneMatrixBoneLocal = rotate * trans * (*m_bones)[i].initMatrixBoneLocal;
			}
		}

		void CVmdController::AdvanceTime()
		{
			m_time++;
		}
	}
}