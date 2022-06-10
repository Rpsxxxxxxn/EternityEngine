#include "Math.h"

namespace Eternity
{
	namespace Utility
	{
		// ��
		const float Math::PI = 3.14159f;

		// �傫���ق���r�o
		float Math::Max(const float v, const float max)
		{
			return v > max ? v : max;
		}

		// �������ق���r�o
		float Math::Min(const float v, const float min)
		{
			return v < min ? v : min;
		}

		// Max��Min�̊ԂɎ��߂�
		float Math::Clamp(float& v, float max, float min)
		{
			v = Math::Max(v, max);
			v = Math::Min(v, min);
			return v;
		}

		// ���`���
		float Math::Lerp(float& from, float& to, float& speed)
		{
			return (to - from) + from * speed;
		}

		// ���W�A���p
		float Math::ToRadian(const float degree)
		{
			return (degree) * (Math::PI / 180.0f);
		}

		// �f�O���[�p
		float Math::ToDegree(const float radian)
		{
			return (radian) * (180.0f / Math::PI);
		}
	}
}