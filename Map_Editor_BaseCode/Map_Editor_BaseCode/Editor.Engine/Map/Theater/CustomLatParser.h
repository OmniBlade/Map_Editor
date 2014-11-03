#include <string>
#include "CustomLAT.h"
#include  "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include  "../../../Editor.FileSystem/IniFile/INISection.hpp"

class INISection;

class CustomLatClass
{
public:
	static CustomLat parseAndGet(INISection* section)
	{
		CustomLat ret;
		std::string theaterSplit;
		section->readStringValue("Name", ret.Name, "No Name - " + section->getValue("LATSetIndex"));
		section->readShortValue("LATSetIndex", ret.LATIndex);
		section->readShortValue("ClearToLATIndex", ret.CTLIndex);
		section->readShortValue("MorphableIndex", ret.MorphableIndex);
		section->readStringValue("Theaters", theaterSplit);

		LineSplitter split(theaterSplit);

		unsigned short i = 0;
		while (i++ < ret.MAX && split.size() > 0)
		{
			ret.TheaterID[i] = split.pop_string();
		}
		return ret;
	}
};
