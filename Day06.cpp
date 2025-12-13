#include "Day06.h"

#include <regex>
#include <numeric>

using namespace std;

void Day06::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<string> lines;
	process_file([&](string const& line, int const& lineNumber) -> bool
	{
		lines.emplace_back(line);
		return true;
	});
	regex patternSign(R"([*+])");
	string& lastLine = lines.back();
	sregex_iterator ite();
	auto words_begin = std::sregex_iterator(lastLine.begin(), lastLine.end(), patternSign);
	auto end = std::sregex_iterator();
	vector<long long> results;
	vector<string> signs;
	// get signs
	for (auto it = words_begin; it != end; it++)
	{
		string const sign = it->str();
		signs.emplace_back(sign);
		if (sign == "+")
		{
			results.emplace_back(0);
		}
		else
		{
			results.emplace_back(1);
		}
	}
	regex patternNumber(R"(\d+)");
	for (size_t lineIndex = 0; lineIndex < lines.size() - 1; lineIndex++)
	{
		string& line = lines.at(lineIndex);
		auto numbers_begin = std::sregex_iterator(line.begin(), line.end(), patternNumber);
		int columnIndex{};
		for (auto it = numbers_begin; it != end; it++)
		{
			long long number = stoll(it->str());
			long long& value = results.at(columnIndex);
			string& sign = signs.at(columnIndex);
			if (sign == "+")
			{
				value += number;
			}
			else
			{
				value *= number;
			}

			columnIndex++;
		}
		cout << endl;
	}
	long long result = accumulate(results.begin(), results.end(), 0LL);
	cout << "result: " << result << endl;
}

void Day06::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<string> lines;
	process_file([&](string const& line, int const& lineNumber) -> bool
	{
		lines.emplace_back(line);
		return true;
	});

	string lastLine = lines.back();
	lines.pop_back();

	vector<long long> results;
	vector<char> signs;
	vector<size_t> signsPositions;
	// get signs
	for (size_t charIndex = 0; charIndex < lastLine.size(); charIndex++)
	{
		char& c = lastLine.at(charIndex);
		if (c != ' ')
		{
			if (c == '+')
			{
				results.emplace_back(0);
			}
			else if (c == '*')
			{
				results.emplace_back(1);
			}
			signsPositions.emplace_back(charIndex);
			signs.emplace_back(c);
		}
	}
	for (size_t signIndex = 0; signIndex < signs.size(); signIndex++)
	{
		//cout << "column " << signIndex << ": \n";
		size_t numberStartIndex = signsPositions.at(signIndex);
		size_t numberEndIndex = signIndex == signs.size() - 1
			                        ? lastLine.length()
			                        : signsPositions.at(signIndex + 1) - 1;
		for (size_t numberCharIndex = numberStartIndex; numberCharIndex < numberEndIndex; numberCharIndex++)
		{
			string numberValue{};
			for (string& line : lines)
			{
				if (line.at(numberCharIndex) != ' ')
				{
					numberValue += line.at(numberCharIndex);
				}
			}
			//cout << numberValue << " ";
			long long& result = results.at(signIndex);
			if (signs.at(signIndex) == '+')
			{
				result += stoll(numberValue);
			}
			else
			{
				result *= stoll(numberValue);
			}
		}
		//cout << endl;
	}

	long long result = accumulate(results.begin(), results.end(), 0LL);
	cout << "result: " << result << endl;
	cout << "Done\n";
}
