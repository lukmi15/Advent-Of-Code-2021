/*Advent of Code 2021, day 1, part 1
Author(s)		: Lukas Mirow
Date of creation	: 12/1/2021
*/

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
	unsigned res = 0;
	int measurement, last_measurement;
	cin >> last_measurement;
	while (not cin.eof())
	{
		cin >> measurement;
		if (measurement > last_measurement)
			res++;
		last_measurement = measurement;
	}
	cout << res << endl;
	return 0;
}
