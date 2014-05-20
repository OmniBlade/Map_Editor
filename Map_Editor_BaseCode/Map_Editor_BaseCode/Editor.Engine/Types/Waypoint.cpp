#include "stdafx.h"
#include "Waypoint.hpp"
#include "../../Log.hpp"

Waypoint::Waypoint(int index_)
:index(index_), letterIndex(getLetterIndex())
{

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
			Log::note("Unable to convert waypoint with letter indx '" + letterIndex + "'", Log::DEBUG);
		}
	}
	else
	{
		Log::note("Unable to convert waypoint with letter indx '" + letterIndex + "'", Log::DEBUG);
	}
	return -1;
}

std::string Waypoint::getLetterIndex()
{
	if (!letterIndex.empty())
		return letterIndex;

	if (index >= 702 || index < 0)
	{
		Log::note("Unable to convert waypoint with index '" + Log::toString(index) + "'", Log::DEBUG);
	}
	else
	{
		float divided = (float) index / 26;
		int letter1 = (int) divided - 1;
		int letter2 = index - 26 * (int) divided;
		char chX = 'A' + letter2;
		char chY = 'A' + letter1;

		std::string result;
		result.push_back(chX);
		result.push_back(chY);
		//std::cout << "Waypoint converted to STRING: " << result << std::endl;

		return result;
	}
	return "";
}