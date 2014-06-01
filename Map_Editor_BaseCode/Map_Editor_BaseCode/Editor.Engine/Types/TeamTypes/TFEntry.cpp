#include "stdafx.h"
#include "TFEntry.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"

TFEntry::TFEntry(const std::string& list)
{
	LineSplitter split(list);

	/*
		At least one of the three should be != nullptr, otherwise the entry is invalid!
	*/
	if (split.pop(count) && split.pop(unit))
	{
		aircraft = AircraftType::Array.find(unit);
		infantry = InfantryType::Array.find(unit);
		vehicle = VehicleType::Array.find(unit);
	}
}
