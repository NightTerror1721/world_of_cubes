#pragma once

#include <cstdint>

class Time
{
private:
	int64_t _microseconds;

public:
	Time();
	Time(const Time& t);
	Time(Time&& t) noexcept;

	Time& operator= (const Time& t);
	Time& operator= (Time&& t) noexcept;

	operator bool() const;

	float asSeconds() const;

	int32_t asMilliseconds() const;

	int64_t asMicroseconds() const;

	static Time seconds(float s);
	static Time milliseconds(int32_t ms);
	static Time microseconds(int64_t mcs);

private:
	explicit Time(int64_t microseconds);



public:
	friend bool operator! (const Time& t);

	friend bool operator== (const Time& t0, const Time& t1);
	friend bool operator!= (const Time& t0, const Time& t1);

	friend bool operator> (const Time& t0, const Time& t1);
	friend bool operator< (const Time& t0, const Time& t1);
	friend bool operator>= (const Time& t0, const Time& t1);
	friend bool operator<= (const Time& t0, const Time& t1);

	friend Time operator- (const Time& t);

	friend Time operator+ (const Time& t0, const Time& t1);
	friend Time& operator+= (Time& t0, const Time& t1);

	friend Time operator- (const Time& t0, const Time& t1);
	friend Time& operator-= (Time& t0, const Time& t1);

	friend Time operator* (const Time& t0, const Time& t1);
	friend Time operator* (const Time& t0, float value);
	friend Time operator* (const Time& t0, int64_t value);
	friend Time& operator*= (Time& t0, const Time& t1);
	friend Time& operator*= (Time& t0, float value);
	friend Time& operator*= (Time& t0, int64_t value);

	friend Time operator/ (const Time& t0, const Time& t1);
	friend Time operator/ (const Time& t0, float value);
	friend Time operator/ (const Time& t0, int64_t value);
	friend Time& operator/= (Time& t0, const Time& t1);
	friend Time& operator/= (Time& t0, float value);
	friend Time& operator/= (Time& t0, int64_t value);

	friend Time operator% (const Time& t0, const Time& t1);
	friend Time& operator%= (Time& t0, const Time& t1);
};

namespace time_literals
{
	Time operator"" _s(long double value);
	Time operator"" _ms(unsigned long long int value);
	Time operator"" _mcs(unsigned long long int value);
}
