#ifndef LUMA_FLOAT_H
#define LUMA_FLOAT_H

// float.h
// (c) 2025 Connor J. Link. All Rights Reserved.

namespace fx
{
	using platform_type = float;

	template<typename T>
	consteval platform_type native(T param)
	{
		return static_cast<platform_type>(param);
	}


	template<typename T = platform_type>
	consteval T pi()
	{
		return T{ 3.14159265358979323846L };
	}

	template<typename T = platform_type>
	consteval T two_pi()
	{
		return 2 * pi();
	}

	template<typename T = platform_type>
	constexpr T radians(T degrees)
	{
		constexpr auto factor = pi() / T{ 180 };
		return degrees * factor;
	}

	template<typename T = platform_type>
	constexpr T degrees(T radians)
	{
		constexpr auto factor = T{ 180 } / pi();
		return radians * factor;
	}
}

#endif
