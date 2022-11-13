/*Advent of Code 2021, day 3, part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/5/2021
*/

#include <iostream>
#include <string>
#include <list>
#include <bitset>
using namespace std;

typedef uint16_t num_t;
constexpr unsigned BITLEN = 16;

//Print message and exit with failure code
void fail(const string& msg)
{
	cerr << msg << endl;
	exit(1);
}

//Find most common bits in given numbers at a given position
//Returns true on 1 and false on 0
bool find_most_common_bit_in_nums_at_pos(const list<num_t>& nums, const unsigned pos)
{

	//Sanity check
	if (pos >= BITLEN)
		throw "pos >= BITLEN";

	//Count 1s
	size_t n1s = 0;
	for (const num_t num : nums)
		if (num & (1 << pos))
			n1s++;

	//Determine most common bit
	const size_t cnums = nums.size();
	if (cnums % 2 == 0)
		return n1s >= cnums / 2; //1 wins in case of draw
	else
		return n1s > cnums / 2;
	return 0;

}

//Filters list of candidates by removing unfitting 1s bit-by-bit
void find_gen_or_scrubber_rating(list<num_t>& candidates, const unsigned numlen, const bool find_scrubber_rating = false)
{
	list<num_t>::iterator tmp, it;
	bool bit_to_keep;
	for (int i = numlen - 1; i >= 0 and candidates.size() > 1; i--)
	{
		{//Debug
			cout << "Candidate list:" << endl;
			for (const num_t cand : candidates)
				cout << bitset<BITLEN>(cand) << endl;
		}
		it = candidates.begin();
		if (find_scrubber_rating)
			bit_to_keep = not find_most_common_bit_in_nums_at_pos(candidates, i);
		else
			bit_to_keep = find_most_common_bit_in_nums_at_pos(candidates, i);
		while (it != candidates.end() and candidates.size() > 1)
		{
			cout << "Bit at pos " << i << " must be " << bit_to_keep << endl;
			if (static_cast<bool>(*it & (1 << i)) != bit_to_keep)
			{
				cout << "Removing candidate " << bitset<BITLEN>(*it) << endl;
				tmp = next(it);
				candidates.erase(it);
				it = tmp;
			}
			else
				it++;
		}
	}
}

int main(int argc, char **argv)
{
	//Read input
	list<num_t> nums;
	char c;
	num_t num;
	unsigned numlen = 0;
	unsigned numlen_tmp = 0;
	while (not cin.eof())
	{
		num = 0;
		numlen_tmp = 0;
		do
		{
			cin.get(c);
			if (c == '1')
			{
				num = (num << 1) | 1;
				numlen_tmp++;
			}
			else if (c == '0')
			{
				num = (num << 1);
				numlen_tmp++;
			}
		}
		while (c != '\n' and not cin.eof());
		if (numlen_tmp > 0)
		{
			nums.push_back(num);
			numlen = numlen_tmp;
		}
	}
	cout << "Length of a diagnostics value is " << numlen << endl;
	cout << "Read diagnostics:" << endl;
	for (const num_t num : nums)
		cout << bitset<BITLEN>(num) << endl;

	//Determine O2 generator rating
	list<num_t> o2gr_candidates(nums);
	find_gen_or_scrubber_rating(o2gr_candidates, numlen);
	cout << "O2 generator rating: 0b" << bitset<BITLEN>(o2gr_candidates.front()) << endl;

	//Determine CO2 scrubber rating
	list<num_t> co2sr_candidates(nums);
	find_gen_or_scrubber_rating(co2sr_candidates, numlen, true);
	cout << "CO2 scrubber rating: 0b" << bitset<BITLEN>(co2sr_candidates.front()) << endl;

	//Calc flag
	cout << "Flag: " << o2gr_candidates.front() * co2sr_candidates.front() << endl;

	return 0;
}
