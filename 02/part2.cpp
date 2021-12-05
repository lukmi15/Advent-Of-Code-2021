/*Advent of Code 2021, day 2, part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/5/2021
*/

#define DEBUG
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
	int horiz_pos = 0;
	int vert_pos = 0;
	int aim = 0;
	string direction;
	int amount;
	do
	{
		cin >> direction;
		cin >> amount;
		if (cin.eof())
			break;
		if (direction == "forward")
		{
			horiz_pos += amount;
			vert_pos += aim * amount;
		}
		else if (direction == "up")
			aim -= amount;
		else if (direction == "down")
			aim += amount;
		else
			cerr << "[Error] Unknown direction '" << direction << '\'' << endl;
#ifdef DEBUG
		if (direction == "forward")
			cerr << "[Debug] Added " << amount << " to horizontal position, a total of " << horiz_pos << " horizontally and " << vert_pos << " vertically" << endl;
		else if (direction == "up")
			cerr << "[Debug] Decreased aim by " << amount << ", a total of " << aim << endl;
		else if (direction == "down")
			cerr << "[Debug] Added " << amount << " to aim, a total of " << aim << endl;
#endif //DEBUG
	}
	while (not cin.eof());
#ifdef DEBUG
	cerr << "[Debug] horiz_pos is '" << horiz_pos << "', vert_pos is '" << vert_pos << '\'' << endl;
#endif //DEBUG
	cout << vert_pos * horiz_pos << endl;
	return 0;
}
