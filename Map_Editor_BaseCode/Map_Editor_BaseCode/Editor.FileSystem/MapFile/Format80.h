#pragma once
#include <vector>

class Format80
{
public:
	Format80();

	static void decodeInto(std::vector<byte>::iterator& srcIter, std::vector<byte>::iterator& itEnd, std::vector<byte>::iterator& destBegin, std::vector<byte>::iterator& destIter);
	static int encodeInto(byte* src, size_t src_len, byte* dest);

	static int writeC1(byte* srcIter, byte* destIter, int& offset, int count);
	static int writeC4(byte* destIter, int count, byte repeatValue);

	static int countSame(byte* src, size_t src_len, unsigned int offset, int maxCount);

};

