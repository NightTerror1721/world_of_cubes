#pragma once

#include "time.h"

class Clock
{
private:
	Time _lastReset;

public:
	Clock();
	Clock(const Clock& c);
	Clock(Clock&& c) noexcept;

	Clock& operator= (const Clock& c);
	Clock& operator= (Clock&& c) noexcept;

	Time getElapsedTime() const;

	Time reset();
};
