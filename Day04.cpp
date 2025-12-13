#include "Day04.h"

using namespace std;


static int rolls_count_around(vector<string> const& rows, int rowIndexToCheck, int columnIndexToCheck)
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

void Day04::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<string> rows;
	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			rows.push_back(line);
			return true;
		});

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
			if (rolls_count_around(rows, rowsIndex, columnIndex) < 4)
			{
				rollsToLift++;
			}
		}
		print_time("Row " + to_string(rowsIndex), begin);
	}

	cout << rollsToLift << endl;
}

void Day04::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	vector<string> rows;
	process_file([&](string const& line, int const& lineNumber) -> bool
		{
			rows.push_back(line);
			return true;
		});

	size_t rowLength = rows[0].length();
	int rollsToLift{};
	int currentRollsToLift;
	int round{ 0 };
	do
	{
		round++;
		currentRollsToLift = 0;
		for (int rowsIndex = 0; rowsIndex < rows.size(); rowsIndex++)
		{
			for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
			{
				if (rows[rowsIndex][columnIndex] != '@')
				{
					continue;
				}
				if (rolls_count_around(rows, rowsIndex, columnIndex) < 4)
				{
					rollsToLift++;
					currentRollsToLift++;
					rows[rowsIndex][columnIndex] = 'X';
				}
			}
		}
		print_time("Round " + to_string(round), begin);
	} while (currentRollsToLift > 0);

	cout << rollsToLift << endl;
}
