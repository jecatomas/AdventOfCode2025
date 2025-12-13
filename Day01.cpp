#include "Day01.h"

using namespace std;

void Day01::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<std::string> lines;
	this->process_file([&](string const& line, int const& lineNumber) -> bool
		{
			lines.push_back(line);
			return true;
		});

	int position = 50;
	int zeroCount = 0;

	for (const string& rotation : lines)
	{
		int sign = rotation[0] == 'L' ? -1 : 1;
		int rotationNumber = stoi(rotation.substr(1));
		int rotationRest = (rotationNumber % 100) * sign;
		position += rotationRest;
		if (position > 99)
		{
			position -= 100;
		}
		else if (position < 0)
		{
			position = 100 + position;
		}
		if (position == 0)
		{
			zeroCount++;
		}
	}

	cout << zeroCount;
}

void Day01::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	std::vector<std::string> lines;

	this->process_file([&](string const& line, int const& lineNumber) -> bool
		{
			lines.push_back(line);
			return true;
		});

	int position = 50;
	int zeroCount = 0;
	int lastPosition = 50;
	for (const std::string& rotation : lines)
	{
		int sign = rotation[0] == 'L' ? -1 : 1;
		int rotationNumber = std::stoi(rotation.substr(1));
		int rotationRest = (rotationNumber % 100) * sign;
		// how many times it goes around
		int zeroExtraCount = rotationNumber / 100;
		zeroCount += zeroExtraCount;
		position += rotationRest;
		if (position > 99)
		{
			position -= 100;
			zeroCount++;
		}
		else if (position < 0)
		{
			position = 100 + position;
			if (lastPosition != 0)
			{
				zeroCount++;
			}
		}
		else if (position == 0)
		{
			zeroCount++;
		}
		lastPosition = position;
	}

	std::cout << zeroCount;
}
