/*Advent of Code 2021, day 3, part 1
Author(s)		: Lukas Mirow
Date of creation	: 12/5/2021
*/

#define DEBUG
#include <iostream>
#include <string>
#include <bitset>
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

#ifdef DEBUG
	cerr << "[Debug] Gamma rate is " << gamma_rate << endl;
	cerr << "[Debug] Epsilon rate is " << epsilon_rate << endl;
#endif //DEBUG
	cout << gamma_rate * epsilon_rate << endl;
	return 0;
}
