#include "stdafx.h"
#include "Waypoint.hpp"
#include "../../Log.hpp"

/* static */ MapObjectList<Waypoint> Waypoint::Array;

Waypoint::Waypoint()
{

}

void Waypoint::parse(const std::string& id, const std::string& list)
{
	index = atoi(id.c_str());
	letterIndex = getLetterIndex();
	ID = letterIndex;

	int coords = atoi(list.c_str());
	loc.x = coords % 1000;
	loc.y = coords / 1000;

	Name = Log::toString(loc.x) + " / " + Log::toString(loc.y);
}

int Waypoint::getIndex()
{
	if (index > -1)
	{
		return index;
	}
	
	int waypointInt = 0;
	int waypoint2Int = 0;

	if (letterIndex.length() > 0)
	{
		if (letterIndex.length() == 1)
		{
			waypointInt = toupper(letterIndex[0]) - 'A';

			return waypointInt;
		}
		else if (letterIndex.length() == 2)
		{
			waypointInt = toupper(letterIndex[0]) - 'A';
			waypoint2Int += toupper(letterIndex[1]) - 'A';// <- only if value is longer than 1

			return (waypointInt + 1) * 26 + waypoint2Int;
		}
		else
		{
			Log::line("Unable to convert waypoint with letter indx '" + letterIndex + "'", Log::DEBUG);
		}
	}
	else
	{
		Log::line("Unable to convert waypoint with letter indx '" + letterIndex + "'", Log::DEBUG);
	}
	return -1;
}

std::string Waypoint::getLetterIndex()
{
	if (!letterIndex.empty())
		return letterIndex;

	if (index >= 702 || index < 0)
	{
		Log::line("Unable to convert waypoint with index '" + Log::toString(index) + "'", Log::DEBUG);
	}
	else
	{
		int divided = index / 26;
		int letter1 = divided - 1;
		int letter2 = index - 26 * divided;
		char chX = 'A' + letter2;
		char chY = 'A' + letter1;

		std::string result;
		if (divided != 0.0f)
			result.push_back(chY);
		result.push_back(chX);
		//std::cout << "Waypoint converted to STRING: " << result << std::endl;

		return result;
	}
	return "";
}