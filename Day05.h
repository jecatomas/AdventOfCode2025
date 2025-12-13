#pragma once
#include "DayBase.h"

class Day05 : public DayBase
{
public:
	explicit Day05(const std::string& file_path)
		: DayBase(file_path)
	{
	}

protected:
	void process01_internal(const std::chrono::steady_clock::time_point& begin) override;
	void process02_internal(const std::chrono::steady_clock::time_point& begin) override;
};
