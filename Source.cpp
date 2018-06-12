
#include "compressor.h"
#include <iostream>
#include <exception>
#include <map>

int main() {
	
	try {
			std::vector<std::pair<char, int>> freqTable = { { 'c', 12 },{ 'a', 5 },{ 'b', 9 },{ 'd', 13 },{ 'f', 45 },{ 'e', 16 } };
			HFCompressor hfAppln;
			hfAppln.loadFrequencyTable(&freqTable);
			std::map<char, std::string> *hfCode = hfAppln.generateHFCode();
			for (auto itr = hfCode->begin(); itr != hfCode->end(); itr++)
				std::cout << itr->first << " : " << itr->second << "\n";

			std::cout << "HF Code for aab - " << hfAppln.encode("aab") << "\n";

			std::cout << "Decoded 110011001110100101 - " << hfAppln.decode("110011001110100101");

	} catch (std::bad_alloc &e) {
		std::cout << "Memory Allocation Failure..." << e.what();
	}
}