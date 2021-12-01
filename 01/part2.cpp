/*Advent of Code 2021, day 1, part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/1/2021
*/

//#define DEBUG
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
	unsigned res = 0; //Final result
	int last_measurements[4]; //We only need to memorize the last 4 measurements to compare 2 measurement windows

	//Cycle through all measurements, creating and comparing the measurment windows
	cin >> last_measurements[0]; //Get first measurement
	for (unsigned i = 1; not cin.eof(); i++) //Increment index and check if last read hit EOF
	{
#ifdef DEBUG
		cerr << "[DEBUG] Read " << last_measurements[(i - 1) % 4] << " eof is " << cin.eof() << " index is " << i << endl;
#endif //DEBUG
		if (i >= 4) //If we have enough data to compare 2 measurement windows
		{
			int lhs_compare = last_measurements[(i ) % 4] + last_measurements[(i + 1) % 4] + last_measurements[(i + 2) % 4]; //Create the left-hand-side measurement window from the first 3 measurements
			int rhs_compare = last_measurements[(i + 1) % 4] + last_measurements[(i + 2) % 4] + last_measurements[(i - 1) % 4]; //Create the right-hand-side measurement window from the last 3 measurements
			if (lhs_compare < rhs_compare) //Compare measurement windows and increment counter
#ifndef DEBUG
				res++;
#else //DEBUG
			{
				res++;
				cerr << "[DEBUG] Increased (" << lhs_compare << " < " << rhs_compare << ')' << endl;
			}
			else if (lhs_compare == rhs_compare)
				cerr << "[DEBUG] No change (" << lhs_compare << " == " << rhs_compare << ')' << endl;
			else
				cerr << "[DEBUG] Decreased (" << lhs_compare << " > " << rhs_compare << ')' << endl;
#endif //DEBUG
		}
		cin >> last_measurements[i % 4]; //Read measuremnt for next iteration for the EOF file to be up-to date when checked (We only know if the read hit EOF after the read was done)
	}
	cout << res << endl; //Output
	return 0;
}
