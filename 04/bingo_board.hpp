/*BingoBoard class for Advent of code day 4
Author(s)		: Lukas Mirow
Date of creation	: 11/14/2022
*/

#ifndef BINGO_BOARD_HPP
#define BINGO_BOARD_HPP

#include <vector>

class BingoBoard
{

	public:
		static constexpr unsigned WIDTH = 5;
		static constexpr unsigned HEIGHT = 5;

	private:
		const std::vector<unsigned> nums;
		std::vector<bool> marked;

	public:

		//Check if this board has a Bingo
		bool has_bingo() const
		{

			//Check horizontal lines
			for (unsigned i = 0; i < HEIGHT; i++)
			{
				bool tmp = true;
				for (unsigned j = 0; j < WIDTH; j++)
					tmp = tmp and marked[i*5 + j];
				if (tmp)
					return tmp;
			}

			//Check vertical lines
			for (unsigned i = 0; i < WIDTH; i++)
			{
				bool tmp = true;
				for (unsigned j = 0; j < HEIGHT; j++)
					tmp = tmp and marked[i*5 + j];
				if (tmp)
					return tmp;
			}

			return false;
		}

		//Calculate score in case of Bingo
		unsigned score(const unsigned last_drawn_num) const
		{
			unsigned ret = 0;
			constexpr unsigned BOARD_SIZE = WIDTH * HEIGHT;

			for (unsigned i = 0; i < BOARD_SIZE; i++)
				if (not marked[i])
					ret += nums[i];

			return ret * last_drawn_num;
		}

		//Mark a number
		void mark(const unsigned num)
		{
			constexpr unsigned BOARD_SIZE = WIDTH * HEIGHT;
			for (unsigned i = 0; i < BOARD_SIZE; i++)
				if (nums[i] == num)
					marked[i] = true;
		}

		BingoBoard() = delete;
		BingoBoard(const std::vector<unsigned> nums) : nums(nums)
		{
			constexpr unsigned BOARD_SIZE = WIDTH * HEIGHT;
			for (unsigned i = 0; i < BOARD_SIZE; i++)
				marked.push_back(false);
		}

		bool is_marked_at(const unsigned i) const {return marked[i];}
		unsigned num_at(const unsigned i) const {return nums[i];}

};

#endif //BINGO_BOARD_HPP
