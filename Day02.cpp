#include "Day02.h"

#include <set>

using namespace std;


void Day02::process01_internal(const std::chrono::steady_clock::time_point& begin)
{
	string input{
		"78847-119454,636-933,7143759788-7143793713,9960235-10043487,44480-68595,23468-43311,89-123,785189-1014654,3829443354-3829647366,647009-692765,2-20,30-42,120909-197026,5477469-5677783,9191900808-9191943802,1045643-1169377,46347154-46441299,2349460-2379599,719196-779497,483556-641804,265244-450847,210541-230207,195-275,75702340-75883143,58-84,2152-3237,3367-5895,1552-2029,9575-13844,6048-8966,419388311-419470147,936-1409,9292901468-9292987321"
	};
	istringstream sInput(input);
	string pair;
	long long sum = 0;
	while (getline(sInput, pair, ','))
	{
		size_t index = pair.find("-");
		long long from = stoll(pair.substr(0, index));
		long long to = stoll(pair.substr(index + 1, pair.length() - 1));

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

void Day02::process02_internal(const std::chrono::steady_clock::time_point& begin)
{
	string input{
		"78847-119454,636-933,7143759788-7143793713,9960235-10043487,44480-68595,23468-43311,89-123,785189-1014654,3829443354-3829647366,647009-692765,2-20,30-42,120909-197026,5477469-5677783,9191900808-9191943802,1045643-1169377,46347154-46441299,2349460-2379599,719196-779497,483556-641804,265244-450847,210541-230207,195-275,75702340-75883143,58-84,2152-3237,3367-5895,1552-2029,9575-13844,6048-8966,419388311-419470147,936-1409,9292901468-9292987321"
	};
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
		print_time("time: ", begin);
	}

	for (string const& number : allInvalid)
	{
		sum += stoll(number);
	}

	cout << sum << endl;
}
