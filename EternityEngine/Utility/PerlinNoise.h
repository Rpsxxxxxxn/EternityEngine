#pragma once

#include "../Includer.h"

namespace Eternity
{
	namespace Utility
	{
		class CPerlinNoise
		{
		public:
			CPerlinNoise(std::uint32_t seed = std::default_random_engine::default_seed);
			void ReSeed(std::uint32_t seed);
			double Noise(double x);
			double Noise(double x, double y);
			double Noise(double x, double y, double z);
			double OctaveNoise(double x, std::int32_t octaves);
			double OctaveNoise(double x, double y, std::int32_t octaves);
			double OctaveNoise(double x, double y, double z, std::int32_t octaves);
		private:
			double Fade(double t) noexcept;
			double Lerp(double t, double a, double b) noexcept;
			double Grad(std::uint8_t hash, double x, double y, double z) noexcept;

			std::uint8_t p[512];
		};
	}
}