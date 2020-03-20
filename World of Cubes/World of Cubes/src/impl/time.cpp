#include "support/time.h"

#include <utility>

Time::Time() :
	_microseconds{}
{}

Time::Time(int64_t microseconds) :
	_microseconds{ microseconds }
{}

Time::Time(const Time& t) :
	_microseconds{ t._microseconds }
{}

Time::Time(Time&& t) noexcept :
	_microseconds{ std::move(t._microseconds) }
{}

Time& Time::operator= (const Time& t)
{
	_microseconds = t._microseconds;
	return *this;
}
Time& Time::operator= (Time&& t) noexcept
{
	_microseconds = std::move(t._microseconds);
	return *this;
}

Time::operator bool() const { return _microseconds; }

float Time::asSeconds() const { return static_cast<float>(_microseconds / 1000000.0); }

int32_t Time::asMilliseconds() const { return static_cast<int32_t>(_microseconds / 1000LL); }

int64_t Time::asMicroseconds() const { return _microseconds; }

Time Time::seconds(float s) { return Time{ static_cast<int64_t>(s * 1000000.0) }; }
Time Time::milliseconds(int32_t ms) { return Time{ static_cast<int64_t>(ms * 1000LL) }; }
Time Time::microseconds(int64_t mcs) { return Time{ mcs }; }


bool operator! (const Time& t) { return !t._microseconds; }

bool operator== (const Time& t0, const Time& t1) { return t0._microseconds == t1._microseconds; }
bool operator!= (const Time& t0, const Time& t1) { return t0._microseconds != t1._microseconds; }

bool operator> (const Time& t0, const Time& t1) { return t0._microseconds > t1._microseconds; }
bool operator< (const Time& t0, const Time& t1) { return t0._microseconds < t1._microseconds; }
bool operator>= (const Time& t0, const Time& t1) { return t0._microseconds >= t1._microseconds; }
bool operator<= (const Time& t0, const Time& t1) { return t0._microseconds <= t1._microseconds; }

Time operator- (const Time& t) { return Time{ -t._microseconds }; }

Time operator+ (const Time& t0, const Time& t1) { return Time{ t0._microseconds + t1._microseconds }; }
Time& operator+= (Time& t0, const Time& t1) { t0._microseconds += t1._microseconds; return t0; }

Time operator- (const Time& t0, const Time& t1) { return Time{ t0._microseconds - t1._microseconds }; }
Time& operator-= (Time& t0, const Time& t1) { t0._microseconds -= t1._microseconds; return t0; }

Time operator* (const Time& t0, const Time& t1) { return Time{ t0._microseconds * t1._microseconds }; }
Time operator* (const Time& t0, float value) { return Time{ static_cast<int64_t>(t0._microseconds * static_cast<double>(value)) }; }
Time operator* (const Time& t0, int64_t value) { return Time{ t0._microseconds * value }; }
Time& operator*= (Time& t0, const Time& t1) { t0._microseconds *= t1._microseconds; return t0; }
Time& operator*= (Time& t0, float value) { t0._microseconds = static_cast<int64_t>(t0._microseconds * static_cast<double>(value)); return t0; }
Time& operator*= (Time& t0, int64_t value) { t0._microseconds *= value; return t0; }

Time operator/ (const Time& t0, const Time& t1) { return Time{ t0._microseconds / t1._microseconds }; }
Time operator/ (const Time& t0, float value) { return Time{ static_cast<int64_t>(t0._microseconds / static_cast<double>(value)) }; }
Time operator/ (const Time& t0, int64_t value) { return Time{ t0._microseconds / value }; }
Time& operator/= (Time& t0, const Time& t1) { t0._microseconds /= t1._microseconds; return t0; }
Time& operator/= (Time& t0, float value) { t0._microseconds = static_cast<int64_t>(t0._microseconds / static_cast<double>(value)); return t0; }
Time& operator/= (Time& t0, int64_t value) { t0._microseconds /= value; return t0; }

Time operator% (const Time& t0, const Time& t1) { return Time{ t0._microseconds % t1._microseconds }; }
Time& operator%= (Time& t0, const Time& t1) { t0._microseconds %= t1._microseconds; return t0; }


namespace time_literals
{
	Time operator"" _s(long double value) { return Time::seconds(static_cast<float>(value)); }
	Time operator"" _ms(unsigned long long int value) { return Time::milliseconds(static_cast<int32_t>(value)); }
	Time operator"" _mcs(unsigned long long int value) { return Time::microseconds(static_cast<int64_t>(value)); }
}
