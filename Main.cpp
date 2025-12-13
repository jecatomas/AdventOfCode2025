
#include <iostream>
#include <string>


#include "Day01.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"

using namespace std;


int main()
{
	try
	{
		Day06 d("input/06.txt");
		d.process02();
	}
	catch (string& e)
	{
		cout << "Error: " << e << endl;
	}

	return 0;
};
