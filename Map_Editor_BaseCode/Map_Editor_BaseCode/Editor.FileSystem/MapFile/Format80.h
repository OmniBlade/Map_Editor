#pragma once
#include <vector>

class Format80
{
public:
	Format80();

	static void decompressInto(byte* src, size_t src_len, byte* destStart, byte* dest);
	static int compressInto(byte* src, size_t src_len, byte* dest);

	static int writeC1(byte* srcIter, byte* destIter, int& offset, int count);
	static int writeC4(byte* destIter, int count, byte repeatValue);

	static int countSame(byte* src, size_t src_len, unsigned int offset, int maxCount);

};

