#pragma once

#include <cmath>
#include <algorithm>

namespace utils
{
	template<typename _Ty>
	constexpr inline _Ty clamp(const _Ty value, const _Ty min, const _Ty max)
	{
		return std::max<_Ty>(min, std::min<_Ty>(max, value));
	}
}

namespace math
{
	template<typename _Ty>
	constexpr inline _Ty abs(const _Ty value) { return value >= 0 ? value : -value ; }

	template<> inline int abs<int>(const int value) { return std::abs(value); }
	template<> inline long int abs<long int>(const long int value) { return std::abs(value); }
	template<> inline long long int abs<long long int>(const long long int value) { return std::abs(value); }
	template<> inline float abs<float>(const float value) { return std::abs(value); }
	template<> inline double abs<double>(const double value) { return std::abs(value); }
	template<> inline long double abs<long double>(const long double value) { return std::abs(value); }


}
