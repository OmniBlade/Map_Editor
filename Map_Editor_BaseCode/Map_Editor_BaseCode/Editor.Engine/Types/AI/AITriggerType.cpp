#include "stdafx.h"
#include "AITriggerType.hpp"
#include "../TeamTypes/TeamType.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <sstream>
#include <stdio.h>
#include "../../../Log.hpp"
#include "../../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<AITriggerType> AITriggerType::Array;

AITriggerType::AITriggerType()
{

}

void AITriggerType::parse(const std::string& id, const std::string& list, bool isGlobal_ /* = false */)
{
	isGlobal = isGlobal_;
	ID = id;
	LineSplitter split(list);
	if (split.pop(Name) && split.pop(tt1) && split.pop(owner) && split.pop(techlevel) && split.pop(aiTriggerType) 
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
			paramValue = (int)bytes[0];
			paramCondition = (int)bytes[1];
		}
		else
		{
			Log::line("Unable to parse HEX string from AITriggerType with ID '" + id + "'.", Log::DEBUG);
		}

		pCountry = Country::Array.find(owner);

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
		Log::line("Unable to parse AITriggerType with ID '" + id + "'.", Log::DEBUG);
	}
}

void AITriggerType::writeToINI(INIFile& file, bool flushNames /* = false */)
{
	for (auto& it : Array.objectList)
	{
		if (!it->isGlobal) // AIMD.INI should NOT go into the map file
		{
			file.SetValue("AITriggerTypes", it->ID, it->asString(flushNames));
		}
	}
}

std::string AITriggerType::asString(bool voidNames /* = false */)
{
	char buffer[512];
	//Don't need to include the ID, so no "%s = "
	sprintf_s(buffer, 512, "%s,%s,%s,%d,%d,%s,%s,%lf,%lf,%lf,%d,%d,%d,%d,%s,%d,%d,%d",
		voidNames ? "flush!" : this->Name.c_str(),
		teamTypeAsString(teamtype1).c_str(),
		this->owner.c_str(),
		this->techlevel,
		this->aiTriggerType,
		this->techType.c_str(),
		createParameters().c_str(),
		this->weight,
		this->minWeight,
		this->maxWeight,
		this->skirmish != 0,
		0,
		this->side,
		this->baseDefense != 0,
		teamTypeAsString(teamtype2).c_str(),
		this->easy != 0,
		this->medium != 0,
		this->hard != 0
		);

	return buffer;

}

std::string AITriggerType::createParameters()
{
	std::string retStr;
	//Herp derp
	const byte MAX = 8;

	//Wooh, tricky hardcoding but AITriggerType expansion will probably never see daylight anyhow...
	int params[MAX] = { paramValue, paramCondition, 0, 0, 0, 0, 0, 0 };
	for (unsigned int i = 0; i < MAX; ++i)
	{
		retStr.append(paramToString(params[i]));
	}

	return retStr;
}

std::string AITriggerType::paramToString(int param)
{
	std::string ret;
	ret.resize(9);
	for (unsigned int i = 0; i < 4; ++i)
	{
		auto bytes = reinterpret_cast<byte*>(&param);
		sprintf_s(&ret[2 * i], ret.size() - 2 * i, "%02X", bytes[i]);
	}
	
	ret.resize(8);
	return ret;
}

std::string AITriggerType::teamTypeAsString(TeamType* pTeamType)
{
	if (!pTeamType)
	{
		return "<none>";
	}
	else
	{
		return pTeamType->ID;
	}
}
