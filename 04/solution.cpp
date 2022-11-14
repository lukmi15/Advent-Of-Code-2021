/*Advent of Code 2021 day 4
Author(s)		: Lukas Mirow
Date of creation	: 11/14/2022
*/

#define DEBUG
#include <iostream>
#include <string>
#include <cctype>
#include "bingo_board.hpp"
using namespace std;

//Read input from standard input
void read_input(vector<unsigned>& draw_nums, vector<BingoBoard*>& boards)
{
	char c;
	string nextint;

	//Parse numbers to be drawn
	while (not cin.eof() and c != '\n')
	{
		cin.get(c);
		if (isdigit(c))
			nextint.push_back(c);
		else if (nextint.length())
		{
			draw_nums.push_back(static_cast<unsigned>(stoi(nextint)));
			nextint = "";
		}
	}

	//Parse boards
	unsigned bnum;
	vector<unsigned> bnums;
	constexpr unsigned BOARD_SIZE = BingoBoard::WIDTH * BingoBoard::HEIGHT;
	cin >> bnum;
	while (not cin.eof())
	{
		bnums.push_back(bnum);
		if (bnums.size() == BOARD_SIZE) //Create and push new board
		{
			boards.push_back(new BingoBoard(bnums));
			bnums.clear();
		}
		cin >> bnum;
	}

}

int main(int argc, char **argv)
{

	//Read input
	vector<unsigned> draw_nums;
	vector<BingoBoard*> boards;
	read_input(draw_nums, boards);

	//Find out which board wins first
	for (const unsigned& draw_num : draw_nums)
		for (BingoBoard& board : boards)
		{
			board.mark(draw_num);
			if (board.has_bingo())
			{
				cout << board.score(draw_num) << endl;;
				return 0;
			}
		}

	return 0;
}
