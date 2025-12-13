#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <iostream>

class DayBase
{
private:
	std::string file_path;

protected:
	void process_file(std::function<bool(std::string const& line, int const& lineNumber)> const& processLine);
	void print_time(std::string const& text, std::chrono::steady_clock::time_point const& begin);
	virtual void process01_internal(std::chrono::steady_clock::time_point const& begin)
	{
	}
	virtual void process02_internal(std::chrono::steady_clock::time_point const& begin)
	{
	}


public:
	DayBase() = default;

	explicit DayBase(const std::string& file_path)
		: file_path(file_path)
	{
	}
	void process01();
	void process02();
};

