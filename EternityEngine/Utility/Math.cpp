#include "Math.h"

namespace Eternity
{
	namespace Utility
	{
		// π
		const float Math::PI = 3.14159f;

		// 大きいほうを排出
		float Math::Max(const float v, const float max)
		{
			return v > max ? v : max;
		}

		// 小さいほうを排出
		float Math::Min(const float v, const float min)
		{
			return v < min ? v : min;
		}

		// MaxとMinの間に収める
		float Math::Clamp(float& v, float max, float min)
		{
			v = Math::Max(v, max);
			v = Math::Min(v, min);
			return v;
		}

		// 線形補間
		float Math::Lerp(float& from, float& to, float& speed)
		{
			return (to - from) + from * speed;
		}

		// ラジアン角
		float Math::ToRadian(const float degree)
		{
			return (degree) * (Math::PI / 180.0f);
		}

		// デグリー角
		float Math::ToDegree(const float radian)
		{
			return (radian) * (180.0f / Math::PI);
		}
	}
}