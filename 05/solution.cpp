/*Advent of Code 2022 day 5
Author(s)		: Lukas Mirow
Date of creation	: 11/14/2022
*/

#define DEBUG
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

constexpr unsigned MAX_X = 9;
constexpr unsigned MAX_Y = 9;

typedef pair<pair<unsigned,unsigned>,pair<unsigned,unsigned>> Line;


void print_map(const vector<unsigned>& map)
{
	for (unsigned y = 0; y < MAX_Y; y++)
	{
		for (unsigned x = 0; x < MAX_X; x++)
			cout << map[x + MAX_X*y];
		cout << endl;
	}
}

void print_line(const Line& line)
{
	cout << line.first.first << ',' << line.first.second << " -> " << line.second.first << ',' << line.second.second << endl;
}

int main(int argc, char **argv)
{

	//Read input
	char c;
	vector<Line> lines;
	unsigned start_x, start_y, end_x, end_y;
	while (not cin.eof())
	{
		for (unsigned i = 0; i < 4; i++)
		{
			cin.get(c);
			if (cin.eof())
				break;
			if (not isdigit(c))
			{
				i--;
				continue;
			}
			if (i == 0)
				start_x = static_cast<unsigned>(c) - static_cast<unsigned>('0');
			else if (i == 1)
				start_y = static_cast<unsigned>(c) - static_cast<unsigned>('0');
			else if (i == 2)
				end_x = static_cast<unsigned>(c) - static_cast<unsigned>('0');
			else
			{
				end_y = static_cast<unsigned>(c) - static_cast<unsigned>('0');
				lines.push_back(Line(pair<unsigned,unsigned>(start_x, start_y), pair<unsigned,unsigned>(end_x, end_y)));
			}
		}
	}

	//Initialize map
	constexpr unsigned MAP_SIZE = MAX_X * MAX_Y;
	vector<unsigned> map;
	for (unsigned i = 0; i < MAP_SIZE; i++)
		map.push_back(0);

	//Draw horizontal and vertical lines
	unsigned x, y;
	for (const Line& line : lines)
	{
		print_line(line);
		if (line.first.first == line.second.first) //Vertical line
		{
			x = line.first.first;
			if (line.first.second <= line.second.second) //Downwards line
				for (y = line.first.second; y <= line.second.second; y++)
					map[x + MAX_X*y]++;
			else //Upwards line
				for (y = line.first.second; y >= line.second.second; y--)
					map[x + MAX_X*y]++;
		}
		else if (line.first.second == line.second.second) //Horizontal line
		{
			y = line.first.second;
			if (line.first.first <= line.second.first) //Line to the right
				for (x = line.first.first; x <= line.second.first; x++)
					map[x + MAX_X*y]++;
			else //Line to the left
				for (x = line.first.first; x >= line.second.first; x--)
					map[x + MAX_X*y]++;
		}
	}
	print_map(map);

	//Get flag for part 1
	unsigned flag1 = 0;
	for (const unsigned& field : map)
		if (field >= 2)
			flag1++;
	cout << flag1 << endl;

	return 0;
}
