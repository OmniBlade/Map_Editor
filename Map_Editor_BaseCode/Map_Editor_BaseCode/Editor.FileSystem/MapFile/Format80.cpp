#include "stdafx.h"
#include "Format80.h"
#include <iostream>

Format80::Format80()
{
}

/* static */  void Format80::decodeInto(std::vector<byte>::iterator& srcIter, std::vector<byte>::iterator& itEnd, std::vector<byte>::iterator& destBegin, std::vector<byte>::iterator& destIter)
{
	while (srcIter != itEnd)
	{
		byte code = *srcIter++;

		//Bit 1 = 0
		if ((code & 0x80) == 0)
		{//Case 2 - command 0
			short count = (code >> 4) + 3;
			int relPos = ((code & 0xf) << 8) | *srcIter++;
			auto copyIter = destIter - relPos;

			while (count-- != 0)
			{
				*destIter++ = *copyIter++;
			}
		}
		//Bit 1 = 1
		else
		{
			int count = code & 0x3F;
			if ((code & 0xC0) == 0x80)
			{//Case 1
				if (count == 0)
				{
					//End of the line, literally
					break;
				}

				while (count-- != 0)
				{
					*destIter++ = *srcIter++;
				}
			}
			else if (code == 0xFE) // Last bit 0
			{//Case 4 - command 3 - fill
				word temp = 0;
				temp |= *srcIter++;
				temp |= *srcIter++ << 8;
				count = temp;
				code = *srcIter++;

				while (count-- != 0)
				{
					*destIter++ = code;
				}
			}
			else if (code == 0xFF)
			{//Case 5 - command 4 - copy
				word temp2 = 0;
				temp2 |= *srcIter++;
				temp2 |= *srcIter++ << 8;
				count = temp2;

				word temp = 0;
				temp |= *srcIter++;
				temp |= *srcIter++ << 8;
				auto copyIter = destBegin + temp;

				while (count-- != 0)
				{
					*destIter++ = *copyIter++;
				}
			}
			else
			{//Case 3 - command 2 - bit 6 = 1
				count += 3;
				word pos = 0;
				pos |= *srcIter++;
				pos |= *srcIter++ << 8;
				auto copyIter = destBegin + pos;

				while (count-- != 0)
				{
					*destIter++ = *copyIter++;
				}
			}
		}
	}
}