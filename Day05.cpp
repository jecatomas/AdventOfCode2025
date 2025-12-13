#include "Day05.h"

using namespace std;

struct Range
{
	long long from;
	long long to;
};

void Day05::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	bool processIngredients{ false };
	int sum{};
	vector<tuple<long long, long long>> ingredientsFresh;
	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			cout << "Line Nr: " << lineNumber << endl;
			if (processIngredients)
			{
				long long ingredientId = stoll(line);
				// todo:
				auto a = ranges::find_if(ingredientsFresh, [ingredientId](tuple<long long, long long> t)
					{
						return get<0>(t) <= ingredientId && ingredientId <= get<1>(t);
					});
				if (a != ingredientsFresh.end())
				{
					sum++;
				}
				return true;
			}
			if (line.empty())
			{
				processIngredients = true;
				return true;
			}
			size_t index = line.find('-');
			long long from = stoll(line.substr(0, index));
			long long to = stoll(line.substr(index + 1, line.length() - index - 1));
			ingredientsFresh.emplace_back(from, to);
			return true;
		});

	cout << sum << endl;
}

void Day05::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<Range> ranges;
	vector<long long> ids;

	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			print_time("Line Nr : " + to_string(lineNumber), begin);
			if (line.empty())
			{
				return false;
			}
			size_t index = line.find('-');
			long long from = stoll(line.substr(0, index));
			long long to = stoll(line.substr(index + 1, line.length() - index - 1));


			bool addRange = true;
			for (vector<Range>::iterator it = ranges.begin(); it < ranges.end();)
			{
				// existing |-------|    |---|
				// new        |---|      |---|
				if (it->from <= from && it->to >= to)
				{
					addRange = false;
					break;
				}
				// existing    |--|       |--|  |--|
				// new      |--------| |-----|  |-----|
				if (it->from >= from && it->to <= to)
				{
					it = ranges.erase(it);
					continue;
				}
				// existing |-----|    |----|
				// new         |----|       |-----|
				if (it->from <= from && it->to >= from && it->to < to)
				{
					from = it->to + 1;
				}
				// existing   |-----|     |--|
				// new      |---|      |--|
				else if (it->from > from && it->from <= to && it->to > to)
				{
					to = it->from - 1;
				}
				it++;
			}
			if (addRange)
			{
				ranges.emplace_back(from, to);
			}
			return true;
		});
	long long sum{};
	for (auto a : ranges)
	{
		sum += (a.to - a.from + 1);
	}
	cout << sum << endl;
}
