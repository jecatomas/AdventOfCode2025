#include <chrono>
#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <climits>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

void printTime(string text, chrono::steady_clock::time_point begin)
{
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout << text << "  -  " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[millisec]" << "\n\n";
}

void measure(string name, function<void(chrono::steady_clock::time_point)> func)
{
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	func(begin);

	printTime(name + ": Total tile = ", begin);
}

void advent01(chrono::steady_clock::time_point begin)
{
	std::ifstream file{ "c:\\Downloads\\AdventOfCode\\1-test.txt" };
	if (!file.is_open())
	{
		throw "File is not open";
	}
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	int position = 50;
	int zeroCount = 0;

	for (const std::string& rotation : lines)
	{
		int sign = rotation[0] == 'L' ? -1 : 1;
		int rotationNumber = std::stoi(rotation.substr(1));
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

	std::cout << zeroCount;
}

void advent01_02(chrono::steady_clock::time_point begin)
{
	std::ifstream file{ "c:\\Downloads\\AdventOfCode\\1-test.txt" };
	if (!file.is_open())
	{
		throw "File is not open";
	}
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	int position = 50;
	int zeroCount = 0;
	int lastPosition = 50;
	for (const std::string& rotation : lines)
	{
		int sign = rotation[0] == 'L' ? -1 : 1;
		int rotationNumber = std::stoi(rotation.substr(1));
		int rotationRest = (rotationNumber % 100) * sign;
		// how many time it go around
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

void advent02(chrono::steady_clock::time_point begin)
{

	string input{ "78847-119454,636-933,7143759788-7143793713,9960235-10043487,44480-68595,23468-43311,89-123,785189-1014654,3829443354-3829647366,647009-692765,2-20,30-42,120909-197026,5477469-5677783,9191900808-9191943802,1045643-1169377,46347154-46441299,2349460-2379599,719196-779497,483556-641804,265244-450847,210541-230207,195-275,75702340-75883143,58-84,2152-3237,3367-5895,1552-2029,9575-13844,6048-8966,419388311-419470147,936-1409,9292901468-9292987321" };
	istringstream sInput(input);
	string pair;
	long long sum = 0;
	while (getline(sInput, pair, ','))
	{
		size_t index = pair.find("-");
		long long from = stoll(pair.substr(0, index));
		long long to = stoll(pair.substr(index +1, pair.length() - 1));

		for (long long value = from; value <= to; value++)
		{
			string valueStr = to_string(value);
			size_t length = valueStr.length();
			if (length % 2 == 0)
			{
				// check
				//cout << index << ", ";
				int half = length / 2;
				string begin = valueStr.substr(0, half);
				string end = valueStr.substr(half, length - 1);
				if (begin.compare(end) == 0)
				{
					// cout << valueStr << ", ";
					sum += value;

				}
			}
			
		}
	}

	cout << sum;
	
}

void advent02_02(chrono::steady_clock::time_point begin)
{
	string input{ "78847-119454,636-933,7143759788-7143793713,9960235-10043487,44480-68595,23468-43311,89-123,785189-1014654,3829443354-3829647366,647009-692765,2-20,30-42,120909-197026,5477469-5677783,9191900808-9191943802,1045643-1169377,46347154-46441299,2349460-2379599,719196-779497,483556-641804,265244-450847,210541-230207,195-275,75702340-75883143,58-84,2152-3237,3367-5895,1552-2029,9575-13844,6048-8966,419388311-419470147,936-1409,9292901468-9292987321" };
	//string input{ "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124" };
	istringstream sInput(input);
	string pair;
	long long sum{};
	set<string> allInvalid;
	int recordCount{};
	while (getline(sInput, pair, ','))
	{
		recordCount++;
		cout << "Line " << recordCount << "   " << pair << endl;
		size_t index = pair.find("-");
		long long from = stoll(pair.substr(0, index));
		long long to = stoll(pair.substr(index + 1, pair.length() - 1));
		for (long long value = from; value <= to; value++)
		{
			string valueStr = to_string(value);
			size_t length = valueStr.length();
			for (size_t partSize = 1; partSize < length; partSize++)
			{
				string partToCheck;
				bool isValid = false;
				// cannot split equally
				if (length % partSize != 0)
				{
					continue;
				}
				size_t partsCount = length / partSize;
				for (size_t partIndex = 0; partIndex < partsCount; partIndex++)
				{
					string part = valueStr.substr(partIndex * partSize, partSize);
					if (partIndex == 0)
					{
						partToCheck = part;
					}
					else if (partToCheck != part)
					{
						isValid = true;
						break;
					}
				}
				if (!isValid)
				{
					allInvalid.insert(valueStr);
					// cout << valueStr << endl;
				}
			}
		}
		printTime("time: ", begin);
		
	}

	for (string number : allInvalid)
	{
		sum += stoll(number);
	}

	cout << sum << endl;

}

void advent03(chrono::steady_clock::time_point begin)
{
	ifstream file{ "c:\\Downloads\\AdventOfCode\\03.txt" };
	if (!file.is_open())
	{
		throw "File is not open";
	}

	string line;
	int sum{ 0 };
	vector<char> numbers;
	for (int n = 9;n >= 1; n--)
	{
		numbers.push_back(to_string(n)[0]);
	}
	while (getline(file, line))
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
	}
	cout << sum;
}

void advent03_02(chrono::steady_clock::time_point begin)
{
	ifstream file{ "c:\\Downloads\\AdventOfCode\\03.txt" };
	if (!file.is_open())
	{
		throw "File is not open";
	}

	string line;
	long long sum{ 0 };
	vector<char> numbersAll;
	for (int n = 9;n >= 1; n--)
	{
		numbersAll.push_back(to_string(n)[0]);
	}
	int lineCount = 0;
	while (getline(file, line))
	{
		lineCount++;
		cout << "Line: " << lineCount << "   " << line << endl;
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
		printTime("", begin);
		/*
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
		*/
		sum += stoll(valueYoltage);
	}
	cout << sum << endl;
}


int rollsCountArround(vector<string> const &rows, int rowIndexToCheck, int columnIndexToCheck)
{
	int rollsCout{};
	for (int rowIndex = rowIndexToCheck - 1; rowIndex <= rowIndexToCheck + 1; rowIndex++)
	{
		for (int columnIndex = columnIndexToCheck - 1; columnIndex <= columnIndexToCheck + 1; columnIndex++)
		{
			if (rowIndex < 0 || columnIndex < 0 || rowIndex >= rows.size() || columnIndex >= rows[0].length())
			{
				continue;
			}
			if (rowIndex == rowIndexToCheck && columnIndex == columnIndexToCheck)
			{
				continue;
			}
			
			if (rows[rowIndex][columnIndex] == '@')
			{
				rollsCout++;
			}
		}
	}
	return rollsCout;
}

void advent04(chrono::steady_clock::time_point begin)
{
	ifstream file("c:\\Downloads\\AdventOfCode\\04.txt");
	if (!file.is_open())
	{
		throw "File is not open";
	}
	vector<string> rows;
	string row;
	while (getline(file, row))
	{
		rows.push_back(row);
	}
	size_t rowLength = rows[0].length();
	int rollsToLift{};
	for (int rowsIndex = 0; rowsIndex < rows.size(); rowsIndex++)
	{
		for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
		{
			if (rows[rowsIndex][columnIndex] != '@')
			{
				continue;
			}
			if (rollsCountArround(rows, rowsIndex, columnIndex) < 4)
			{
				rollsToLift++;
			}
		}
		printTime("Row " + to_string(rowsIndex), begin);
	}

	cout << rollsToLift << endl;
}

int main() {

	// Source - https://stackoverflow.com/a
// Posted by user3762106, modified by community. See post 'Timeline' for change history
// Retrieved 2025-12-03, License - CC BY-SA 4.0

//***C++11 Style:***

	measure("main", advent04);
	
    return 0;
};