#pragma once

#include "IList.h"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../Editor.Objects.Westwood/Types/VehicleType.hpp"

class TechnoList : public IList
{
public:
	List getList()
	{
		List items;

		unsigned int countBT = BuildingType::Array.count();
		for (unsigned int i = 0; i < countBT; ++i)
		{
			BuildingType* item = BuildingType::Array.get(i);
			if (item->valid)
			{
				add(items, item->Name, i, item->ID, item->WUIName);
			}
		}

		unsigned int countAT = AircraftType::Array.count();
		for (unsigned int i = 0; i < countAT; ++i)
		{
			AircraftType* item = AircraftType::Array.get(i);
			if (item->valid)
			{
				add(items, item->Name, i, item->ID, item->WUIName);
			}
		}

		unsigned int countIT = InfantryType::Array.count();
		for (unsigned int i = 0; i < countIT; ++i)
		{
			InfantryType* item = InfantryType::Array.get(i);
			if (item->valid)
			{
				add(items, item->Name, i, item->ID, item->WUIName);
			}
		}

		unsigned int countVT = VehicleType::Array.count();
		for (unsigned int i = 0; i < countVT; ++i)
		{
			VehicleType* item = VehicleType::Array.get(i);
			if (item->valid)
			{
				add(items, item->Name, i, item->ID, item->WUIName);
			}
		}


		return items;
	};
};