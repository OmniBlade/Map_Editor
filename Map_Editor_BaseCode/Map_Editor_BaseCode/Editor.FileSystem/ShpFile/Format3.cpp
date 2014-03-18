#include "stdafx.h"
#include "Format3.hpp"
#include <iostream>

Format3::Format3()
{
}


Format3::~Format3()
{
}

void Format3::decode(std::vector<byte>& readBytes, std::vector<byte>& rawImageData, int width, int height)
{
	rawImageData.resize(width * height);
	byte* r = &readBytes[0];
	byte* w = &rawImageData[0];

	for (int y = 0; y < height; y++) 
	{
		unsigned short count = (*(unsigned short*)r) - 2;;
		r += 2;
		int x = 0;
		while (count-- > 0) 
		{
			byte v = *r++;
			if (v != 0) 
			{
				x++;
				*w++ = v;
			}
			else
			{
				count--;
				v = *r++;
				if (x + v > width)
					v = (byte)(width - x);
				x += v;
				while (v-- != 0)
					*w++ = 0;
			}
		}
	}
}