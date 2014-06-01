#include "stdafx.h"
#include "AITriggerType.hpp"
#include "../TeamTypes/TeamType.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <sstream>
#include "../../../Log.hpp"
#include "../../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"

/* static */ ObjectList<AITriggerType> AITriggerType::Array;

AITriggerType::AITriggerType()
{

}

void AITriggerType::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);
	if (split.pop(name) && split.pop(tt1) && split.pop(owner) && split.pop(techlevel) && split.pop(aiTriggerType) 
		&& split.pop(techType) && split.pop(parameterString) && split.pop(weight) && split.pop(minWeight)
		&& split.pop(maxWeight) && split.pop(skirmish) && split.pop(unknown) && split.pop(side) && split.pop(baseDefense) && split.pop(tt2) 
		&& split.pop(easy) && split.pop(medium) && split.pop(hard))
	{

		int bytes[8];
		if (parameterString.size() == 64)
		{
			for (unsigned int i = 0; i < 32; i++)
			{
				auto subCount = parameterString.substr(2 * i, 2);
				unsigned long byte = strtoul(subCount.c_str(), NULL, 16);

				unsigned char* byte2 = reinterpret_cast<unsigned char*>(&bytes[0]);
				byte2[i] = byte;
			}
			paramNumber = (int)bytes[0];
			paramEquation = (int)bytes[1];
		}
		else
		{
			Log::note("Unable to parse HEX string from AITriggerType with ID '" + id + "'.", Log::DEBUG);
		}

		/*
			TODO:
			Whether to keep TT* or leave it out!
		*/
		if (tt1 != "<none>")
		{
			teamtype1 = TeamType::Array.find(tt1);
		}
		if (tt2 != "<none>")
		{
			teamtype2 = TeamType::Array.find(tt2);
		}
		if (techType != "<none>")
		{
			pInfantryType = InfantryType::Array.find(techType);
			if (!pInfantryType)
			{
				pBuildingType = BuildingType::Array.find(techType);
				if (!pBuildingType)
				{
					pVehicleType = VehicleType::Array.find(techType);
					if (!pVehicleType)
					{
						pAircraftType = AircraftType::Array.find(techType);
					}
				}
			}
		}
	}
	else
	{
		Log::note("Unable to parse AITriggerType with ID '" + id + "'.", Log::DEBUG);
	}
}

std::string AITriggerType::asString()
{
	std::stringstream returnString;
	
	returnString << name << ',' << tt1 << ',' << owner << ',' << techlevel << ',' << aiTriggerType << ',' << techType << ','
		<< createParameters() << ',' << weight << ',' << minWeight << ',' << maxWeight << ',' << skirmish << ',' << unknown
		<< ',' << side << ',' << baseDefense << ',' << tt2 << ',' << easy << ',' << medium << ',' << hard;

	return returnString.str();
}

std::string AITriggerType::createParameters()
{
	std::string ret;



	return ret;
}