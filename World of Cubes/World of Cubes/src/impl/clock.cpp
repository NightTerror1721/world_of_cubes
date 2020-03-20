#include "support/clock.h"

#include <chrono>
#include <utility>

static inline Time current_time()
{
	return Time::microseconds(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

Clock::Clock() :
	_lastReset{ current_time() }
{}

Clock::Clock(const Clock& c) :
	_lastReset{ c._lastReset }
{}

Clock::Clock(Clock&& c) noexcept :
	_lastReset{ std::move(c._lastReset) }
{}

Clock& Clock::operator= (const Clock& c)
{
	_lastReset = c._lastReset;
	return *this;
}
Clock& Clock::operator= (Clock&& c) noexcept
{
	_lastReset = std::move(c._lastReset);
	return *this;
}

Time Clock::getElapsedTime() const
{
	return current_time() - _lastReset;
}

Time Clock::reset()
{
	Time et = getElapsedTime();
	_lastReset = current_time();
	return std::move(et);
}
