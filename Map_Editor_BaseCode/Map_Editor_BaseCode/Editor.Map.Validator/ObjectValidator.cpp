#include "stdafx.h"
#include "ObjectValidator.hpp"
#include "../Log.hpp"
#include "../Config.hpp"

#include "../Editor.Engine/Types/Objects/Aircraft.hpp"
#include "../Editor.Engine/Types/Objects/Infantry.hpp"
#include "../Editor.Engine/Types/Objects/Terrain.hpp"
#include "../Editor.Engine/Types/Objects/Structure.hpp"
#include "../Editor.Engine/Types/Objects/Unit.hpp"
#include "../Editor.Objects.Westwood/Types/Country.hpp"

ObjectValidator::ObjectValidator()
{
	//Aircraft
	validateAircraft();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Infantry
	validateInfantry();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Units
	validateUnit();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Structures
	validateStructure();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Terrain
	validateTerrain();
	Log::finishErrorRound();
	Log::finishWarningRound();
}

ObjectValidator::~ObjectValidator()
{
}

void ObjectValidator::validateAircraft()
{
	Log::line();
	Log::line("Validating [Aircraft] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Aircraft::Array.objectTypeList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::line("Aircraft at index '" + Log::toString(index) + "' has no valid Country as owner.", Log::ERROR_BUFFER);
		//AircraftType
		if (!it->pAircraft)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has no valid AircraftType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::line("Aircraft at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateInfantry()
{
	Log::line();
	Log::line("Validating [Infantry] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Infantry::Array.objectTypeList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
				Log::line("Infantry at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//InfantryType
		if (!it->pInfantry)
			Log::line("Infantry at index '" + Log::toString(index) + "' has no valid InfantryType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//subCell
		if (it->subCell < 0 || it->subCell > 3)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid sub-Cell set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::line("Infantry at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateUnit()
{
	Log::line();
	Log::line("Validating [Units] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Unit::Array.objectTypeList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::line("Unit at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//VehicleType
		if (!it->pVehicle)
			Log::line("Unit at index '" + Log::toString(index) + "' has no valid VehicleType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateTerrain()
{
	Log::line();
	Log::line("Validating [Terrain] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Terrain::Array.objectTypeList)
	{
		//TerrainType
		if (!it->pTerrainType)
			Log::line("Terrain at index '" + Log::toString(index) + "' has no valid TerrainType set.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::line("Unit at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateStructure()
{
	Log::line();
	Log::line("Validating [Structures] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Structure::Array.objectTypeList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::line("Structure at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//Building
		if (!it->pBuilding)
			Log::line("Structure at index '" + Log::toString(index) + "' has no valid BuildingType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Spotligh
		if (it->spotlight < 0 || it->spotlight > 3)
			Log::line("Structure at index '" + Log::toString(index) + "' has an invalid Spotlight behaviour set.", Log::ERROR_BUFFER);		
		//Powerup1
		/* TODO: Additional pUgradeBuilding check */
		if (it->powerupOne != "None" && it->powerupCount < 1)
			Log::line("Structure at index '" + Log::toString(index) + "' has Powerup #1 set while count is lower than 1.", Log::WARNING);
		//Powerup2
		if (it->powerupTwo != "None" && it->powerupCount < 2)
			Log::line("Structure at index '" + Log::toString(index) + "' has Powerup #2 set while count is lower than 2.", Log::WARNING);
		//Powerup2
		if (it->powerupThree != "None" && it->powerupCount < 3)
			Log::line("Structure at index '" + Log::toString(index) + "' has Powerup #3 set while count is lower than 3.", Log::WARNING);

		index++;
	}
}