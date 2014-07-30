#pragma once
#include <vector>

class Format80
{
public:
	Format80();

	static void decodeInto(std::vector<byte>::iterator& srcIter, std::vector<byte>::iterator& itEnd, std::vector<byte>::iterator& destBegin, std::vector<byte>::iterator& destIter);

};

