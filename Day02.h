#pragma once
#include "DayBase.h"

class Day02 : public DayBase
{
public:
	Day02() = default;

protected:
	void process01_internal(const std::chrono::steady_clock::time_point& begin) override;
	void process02_internal(const std::chrono::steady_clock::time_point& begin) override;
};
