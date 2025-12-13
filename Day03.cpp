#include "Day03.h"

#include <vector>

using namespace std;

void Day03::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	int sum{ 0 };
	vector<char> numbers;
	for (int n = 9; n >= 1; n--)
	{
		numbers.push_back(to_string(n)[0]);
	}

	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			size_t lastIndex = line.length() - 1;
			char number1;
			char number2;
			size_t numberFirstIndex = 0;
			for (char number : numbers)
			{
				size_t index = line.find(number);
				if (index == string::npos || index == lastIndex)
				{
					continue;
				}
				number1 = number;
				numberFirstIndex = index;
				break;
			}

			for (char number : numbers)
			{
				size_t index = line.find(number, numberFirstIndex + 1);
				if (index == string::npos)
				{
					continue;
				}
				number2 = number;
				break;
			}
			string valueStr{};
			valueStr += number1;
			valueStr += number2;

			sum += stoi(valueStr);
			return true;
		});

	cout << sum;
}

void Day03::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	long long sum{ 0 };
	vector<char> numbersAll;
	for (int n = 9; n >= 1; n--)
	{
		numbersAll.push_back(to_string(n)[0]);
	}
	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			cout << "Line: " << lineNumber << "   " << line << endl;
			size_t lastIndexMax = line.length() - 11;
			vector<char> numbersToCheck{ numbersAll };

			string valueYoltage{};
			size_t numberFirstIndex = -1;
			for (auto it = numbersToCheck.begin(); it < numbersToCheck.end();)
			{
				if (valueYoltage.length() == 12)
				{
					break;
				}
				//cout << (*it) << endl;
				size_t charIndex = line.find(*it, numberFirstIndex + 1);
				if (charIndex == string::npos)
				{
					it = numbersToCheck.erase(it);
					continue;
				}
				if (charIndex < lastIndexMax)
				{
					valueYoltage += line[charIndex];
					numberFirstIndex = charIndex;
					lastIndexMax++;
					it = numbersToCheck.begin();
					continue;
				}
				it++;
				if (it == numbersToCheck.end() && valueYoltage.length() != 12)
				{
					it = numbersToCheck.begin();
				}
			}
			cout << "Yoltage: " << valueYoltage << endl;
			print_time("", begin);

			sum += stoll(valueYoltage);
			return true;
		});
	cout << sum << endl;
}
