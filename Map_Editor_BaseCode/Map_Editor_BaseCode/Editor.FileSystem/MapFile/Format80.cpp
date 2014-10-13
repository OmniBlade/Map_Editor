#include "stdafx.h"
#include "Format80.h"
#include <iostream>
#include <algorithm>

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
		{//Case 2 - command 2
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
			{//Case 1 - command 1 - raw copy
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
			{//Case 4 - command 4 - fill
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
			{//Case 5 - command 5 - copy
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
			{//Case 3 - command 3 - bit 6 = 1
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

int Format80::encodeInto(byte* src, size_t src_len, byte* dest)
{
	//std::vector<byte> dest(src.size());
	int finalDestSize = 0;
	byte* pDest = &dest[0];
	auto offset = 0;
	auto left = src_len-2;
	auto blockStart = 0;

	finalDestSize += writeC1(&src[offset], &pDest[finalDestSize], offset, 1);

	while (offset < left)
	{
		auto repeatCount = countSame(src, src_len-1, offset, 0xFFFF);

		if (repeatCount >= 4)
		{
			/* COMMAND 4 */
			finalDestSize += writeC4(&pDest[finalDestSize], repeatCount, src[offset]);

			offset += repeatCount;
			blockStart = offset;
		}
		else
		{
			/* COMMAND 1 */
			//Offset is incremented in writeC1 (passed as reference)
			finalDestSize += writeC1(&src[offset], &pDest[finalDestSize], offset, repeatCount);
		}
	}

	finalDestSize += writeC1(&src[offset], &pDest[finalDestSize], offset, 1);

	//Write what we haven't written up to now

	// Write terminator
	pDest[finalDestSize] = 0x80;
	++finalDestSize;

	return finalDestSize;
}

int Format80::writeC1(byte* src, byte* dest, int& offset, int count)
{
	int writtenBytes = 0;

	if (count <= 0) return writtenBytes;

	auto realCount = std::min(count, 0x3F);
	byte cmd1Byte = 0x80;
	byte firstByte = (cmd1Byte | realCount);

	*dest++ = firstByte;
	++writtenBytes;

	writtenBytes += realCount;
	offset += realCount;

	while (realCount-- > 0)
	{
		*dest++ = *src++;
	}

	return writtenBytes;
}

int Format80::writeC4(byte* dest, int count, byte repeatValue)
{
	byte cmd4byte = 0xFE;
	byte lowByte = static_cast<byte>(count & 0xFF);
	byte highByte = static_cast<byte>(count >> 8);

	*dest++ = cmd4byte;
	*dest++ = lowByte;
	*dest++ = highByte;
	*dest++ = repeatValue;

	return 4;
}

int Format80::countSame(byte* src, size_t src_len, unsigned int offset, int maxCount)
{
	auto srcSize = src_len;

	maxCount = std::min(static_cast<int>((srcSize - offset)), maxCount);
	if (maxCount <= 0)
		return 0;

	auto first = src[offset++];
	auto count = 1;

	while (count < maxCount && src[offset++] == first)
		count++;

	return count;
}
