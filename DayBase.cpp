#include "DayBase.h"

#include <fstream>
#include <iostream>
#include <chrono>

void DayBase::process_file(std::function<bool(std::string const& line, int const& lineNumber)> const& processLine)
{
	if (this->file_path.empty())
	{
		throw "file_path is not set";
	}
	std::cout << "Reading file: " << this->file_path << std::endl;
	std::ifstream file{ this->file_path };
	if (!file.is_open())
	{
		throw "File is not open";
	}
	std::string line;
	int lineNumber{};

	while (getline(file, line))
	{
		lineNumber++;

		if (!processLine(line, lineNumber))
		{
			break;
		}
	}
}

void DayBase::print_time(std::string const& text, std::chrono::steady_clock::time_point const& begin)
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << text << "  -  " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[millisecond]" <<
		"\n\n";
}

void DayBase::process01()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	this->process01_internal(begin);

	print_time("\nTotal tile = ", begin);
}

void DayBase::process02()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	this->process02_internal(begin);

	print_time("\nTotal tile = ", begin);
}
