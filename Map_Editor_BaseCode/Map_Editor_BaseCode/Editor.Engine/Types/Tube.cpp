#include "stdafx.h"
#include "Tube.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"

/* static */ MapObjectList<Tube> Tube::Array;

Tube::Tube()
{
}


void Tube::parse(const std::string& id, const std::string& entry)
{
	ID = id;
	LineSplitter split(entry);
	split.pop(startX);
	split.pop(startY);
	split.pop(direction);
	split.pop(endX);
	split.pop(endY);

	for (unsigned int i = 5; i < 99; ++i)
	{
		steps.push_back(split.peekFromIndex_int(i));
		if (split.peekFromIndex_int(i) == -1)
		{
			break;
		}
	}
}