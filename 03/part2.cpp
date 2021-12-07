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
	string o2_rating, co2_rating;
	bool o2_rating_found = false;
	bool co2_rating_found = false;

	//Reverse approach: Test if a regex matches taking away bits from the back
	for (unsigned i = 0; i < numlen - 1; i++) //For each bit in the number
	{

		//Create regexes
		stringstream gamma_regexp_ss, epsilon_regexp_ss;
		gamma_regexp_ss << "/^";
		epsilon_regexp_ss << "/^";
		bitset<8> gamma_bits(gamma_rate), epsilon_bits(epsilon_rate);
		for (unsigned j = 0; j < numlen - i; j++) //Add the actual value for the bits
		{
			gamma_regexp_ss << gamma_bits[j];
			epsilon_regexp_ss << gamma_bits[j];
		}
		for (unsigned j = numlen - i; j < numlen; j++) //Fill the rest with placeholders
		{
			gamma_regexp_ss << '.';
			epsilon_regexp_ss << '.';
		}
		gamma_regexp_ss << "$/";
		epsilon_regexp_ss << "$/";
		regex gamma_regexp(gamma_regexp_ss.str());
		regex epsilon_regexp(epsilon_regexp_ss.str());
#ifdef DEBUG
		cout << "[Debug] Crafted gamma regexp " << gamma_regexp_ss.str() << " for iteration " << i << endl;
		cout << "[Debug] Crafted epsilon regexp " << epsilon_regexp_ss.str() << " for iteration " << i << endl;
#endif //DEBUG

		//Look for matches
		for (string num : nums)
		{
			if (not o2_rating_found and regex_match(num, gamma_regexp))
			{
				o2_rating = num;
				o2_rating_found = true;
			}
			if (not co2_rating_found and regex_match(num, epsilon_regexp))
			{
				co2_rating = num;
				co2_rating_found = true;
			}
		}
		if (o2_rating_found and co2_rating_found) //If we found both solutions, we can stop
			break;
	}

#ifdef DEBUG
	if (o2_rating_found)
		cerr << "[Debug] o2 rating was found and is is " << o2_rating << endl;
	else
		cerr << "[Debug] o2 rating was not found" << endl;
	if (co2_rating_found)
		cerr << "[Debug] co2 rating was found and is is " << co2_rating << endl;
	else
		cerr << "[Debug] co2 rating was not found" << endl;
#endif //DEBUG
	if (o2_rating_found and co2_rating_found)
		cout << gamma_rate * epsilon_rate << endl;
	else
	{
		cout << "Failed to find o2 and co2 ratings" << endl;
		return 1;
	}
	return 0;
}
