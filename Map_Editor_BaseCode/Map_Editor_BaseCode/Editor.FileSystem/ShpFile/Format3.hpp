#pragma once
#include <vector>

class Format3
{
public:
	Format3();
	~Format3();

	static void decode(std::vector<byte>& readBytes, std::vector<byte>& rawImageData, int width, int height);

};

