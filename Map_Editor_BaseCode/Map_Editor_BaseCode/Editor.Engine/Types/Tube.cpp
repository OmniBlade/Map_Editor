#include "stdafx.h"
#include "Tube.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Log.hpp"
#include <sstream>

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

void Tube::writeToINI(INIFile& file)
{
	for (auto& it : Array.objectList)
	{
		std::stringstream number;
		int i = 0;
		for (auto& it : Array.objectList)
		{
			number << i;
			file.SetValue("Tubes", number.str(), it->asString());
			++i;
			number.str(std::string());
		}
	}
}

std::string Tube::asString()
{
	std::stringstream ret;

	ret << startX << ',' << startY << ',' << direction << ',' << endX << ',' << endY;

	for (auto& it : steps)
	{
		if (it == -1)
		{
			break;
		}
		else
		{
			ret << ',' << it;
		}
	}

	ret << ",-1";

	return ret.str();
}