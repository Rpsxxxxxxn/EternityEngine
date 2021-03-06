#pragma once

namespace Eternity
{
	namespace Utility
	{
		class Math
		{
		public:
			// 大きいほうを排出
			static float Max(const float v, const float max);

			// 小さいほうを排出
			static float Min(const float v, const float min);

			// MaxとMinの間に収める
			static float Clamp(float& v, float max, float min);

			// 線形補間
			static float Lerp(float& from, float& to, float& speed);

			// ラジアン角
			static float ToRadian(const float degree);

			// デグリー角
			static float ToDegree(const float radian);

			// π
			static const float PI;
		};
	}
}