#ifndef FLUX_RANDOM_H
#define FLUX_RANDOM_H

#include "base.h"
#include "types.h"

// random.h
// (c) 2025 Connor J. Link. All Rights Reserved.

namespace fx
{
	class Random
	{
	public:
		static void init();

		static std::uint32_t uint();
		static std::uint32_t uint(std::uint32_t min, std::uint32_t max);

		static float real();

		static fx::vec3 vec3();
		static fx::vec3 vec3(float, float);
		static fx::vec3 vec3_sphere();

	private:
		static std::mt19937 _engine;
		static std::uniform_int_distribution<std::mt19937::result_type> _distribution;
	};

}

#endif
