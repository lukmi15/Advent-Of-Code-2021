/*Advent of Code 2021, day 3, part 2
Author(s)		: Lukas Mirow
Date of creation	: 12/5/2021
*/

#define DEBUG
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <regex>
#include <sstream>
using namespace std;

void fail(const string& msg)
{
	cerr << msg << endl;
	exit(1);
}

int main(int argc, char **argv)
{
	uint32_t gamma_rate = 0;
	uint32_t epsilon_rate = 0;
	constexpr size_t BITLENGTH = 32;
	string num_msb;
	unsigned high_bit_counts_msb[BITLENGTH] = {0};
	unsigned number_count = 0;
	size_t numlen;
	vector<string> nums;

	//Go through all numbers
	do
	{

		//Get number and check for validity
		cin >> num_msb;
		if (cin.eof())
			break;
		numlen = num_msb.length();
		if (numlen > 32)
		{
			cerr << "[Error] read number '" << num_msb << "' but its length is '" << numlen << "' as opposted to the maximum bitlength of '" << BITLENGTH << '\'' << endl;
			return 1;
		}
		nums.push_back(num_msb);
#ifdef DEBUG
		cerr << "[Debug] Num length is " << numlen << endl;
#endif //DEBUG

		//Count bits
		for (size_t i = 0; i < numlen; i++)
		{
			char bit = num_msb[i];
			if (bit == '1')
				high_bit_counts_msb[i]++;
#ifdef DEBUG
			cerr << "[Debug] Bit " << i << " of number " << number_count + 1 << " is " << bit << endl;
			cerr << "[Debug] New high bit counts: {";
			for (unsigned j = 0; j < BITLENGTH - 1; j++)
				cerr << high_bit_counts_msb[j] << ", ";
			cerr << high_bit_counts_msb[BITLENGTH - 1] << "}" << endl;
#endif //DEBUG
		}
		number_count++; //And numbers

	}
	while (not cin.eof());

	//Generate gamma and epsilon rates
	for (unsigned i = 0; i < numlen; i++)
	{
		if (high_bit_counts_msb[i] > number_count / 2)
		{
			gamma_rate |= (0x1 << (numlen - 1 - i));
#ifdef DEBUG
			bitset<8> g(gamma_rate);
			cerr << "[Debug] Adding 1 in gamma rate on position " << numlen - 1 - i << ", gamma rate is now " << g << endl;
#endif //DEBUG
		}
		else
		{
			epsilon_rate |= (0x1 << (numlen - 1 - i));
#ifdef DEBUG
			bitset<8> e(epsilon_rate);
			cerr << "[Debug] Adding 1 in epsilon rate on position " << numlen - 1 - i << ", epsilon rate is now " << e << endl;
#endif //DEBUG
		}
	}

	//Find oxygen generator rating and co2 scrubber rating
	vector<string> o2_candidates, co2_candidates;
	vector<string> o2_chosen(nums), co2_chosen(nums);
	string o2_rating, co2_rating;
	for (size_t bit = 0; bit < numlen; bit++)
	{

		//Oxygen generator rating
		if (o2_chosen.size() > 1)
		{

			//Switch vectors to prepare for the next run
			o2_candidates = o2_chosen;
			o2_chosen.clear();

			//Consider
			for (string num : o2_candidates)
				if (num[bit] == gamma_rate[bit])
					o2_chosen.push_back(num);

		}

		//CO2 scrubber rating
		if (co2_chosen.size() > 1)
		{

			//Switch vectors to prepare for the next run
			co2_candidates = co2_chosen;
			co2_chosen.clear();

			//Consider
			for (string num : co2_candidates)
				if (num[bit] == epsilon_rate[num])
					co2_chosen.push_back(num);

		}

		//Test if we are done
		if (o2_chosen.size() == 1 and co2_chosen.size() == 1)
		{
			o2_rating = o2_chosen[0];
			co2_rating = co2_chosen[0];
			break;
		}

	}
#ifdef DEBUG
	cerr << "[Debug] O2 rating is " << o2_rating << endl;
	cerr << "[Debug] CO2 rating is " << co2_rating << endl;
#endif //DEBUG

	//Transform strings to numbers
	unsigned o2_generator_rating;
	unsigned co2_scrubber_rating;
	//TODO

	//Output
	cout << "The result is " << (o2_generator_rating * co2_scrubber_rating) << endl;
	return 0;
}
