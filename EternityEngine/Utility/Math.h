#pragma once

namespace Eternity
{
	namespace Utility
	{
		class Math
		{
		public:
			// �傫���ق���r�o
			static float Max(const float v, const float max);

			// �������ق���r�o
			static float Min(const float v, const float min);

			// Max��Min�̊ԂɎ��߂�
			static float Clamp(float& v, float max, float min);

			// ���`���
			static float Lerp(float& from, float& to, float& speed);

			// ���W�A���p
			static float ToRadian(const float degree);

			// �f�O���[�p
			static float ToDegree(const float radian);

			// ��
			static const float PI;
		};
	}
}