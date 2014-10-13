#include "stdafx.h"
#include "ObjectValidator.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"

#include "../../Editor.Engine/Types/Objects/Aircraft.hpp"
#include "../../Editor.Engine/Types/Objects/Infantry.hpp"
#include "../../Editor.Engine/Types/Objects/Terrain.hpp"
#include "../../Editor.Engine/Types/Objects/Structure.hpp"
#include "../../Editor.Engine/Types/Objects/Unit.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"

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
	Log::validatorLine();
	Log::validatorLine("Validating [Aircraft] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Aircraft::Array.objectList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has no valid Country as owner.", Log::ERROR_BUFFER);
		//AircraftType
		if (!it->pAircraft)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has no valid AircraftType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::validatorLine("Aircraft at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateInfantry()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Infantry] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Infantry::Array.objectList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
				Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//InfantryType
		if (!it->pInfantry)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has no valid InfantryType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//subCell
		if (it->subCell < 0 || it->subCell > 3)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid sub-Cell set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::validatorLine("Infantry at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateUnit()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Units] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Unit::Array.objectList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//VehicleType
		if (!it->pVehicle)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has no valid VehicleType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//mission
		/* TODO: Add lookup in new class for mission control! */
		if (it->mission.empty())
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid mission set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Veterancy
		if (it->veterancy < 0)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid veterancy set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateTerrain()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Terrain] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Terrain::Array.objectList)
	{
		//TerrainType
		if (!it->pTerrainType)
			Log::validatorLine("Terrain at index '" + Log::toString(index) + "' has no valid TerrainType set.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::validatorLine("Unit at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		index++;
	}
}

void ObjectValidator::validateStructure()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Structures] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Structure::Array.objectList)
	{
		//Owner
		if (!it->pCountry && !it->pHouse && (!Config::isSP && !it->pCountry->MultiplayPassive))
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has no valid Owner set.", Log::ERROR_BUFFER);
		//Building
		if (!it->pBuilding)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has no valid BuildingType set.", Log::ERROR_BUFFER);
		//Health
		if (it->health < 0)// || it->health > 255)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid amount of health.", Log::ERROR_BUFFER);
		//LocX
		if (it->loc.x < 0)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		//LocY
		if (it->loc.y < 0)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		//direction
		if (it->direction < 0 || it->direction > 255)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid direction set.", Log::ERROR_BUFFER);
		//Tag
		if (!it->pTag && it->tag != "None")
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid Tag set.", Log::ERROR_BUFFER);
		//Spotligh
		if (it->spotlight < 0 || it->spotlight > 3)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has an invalid Spotlight behaviour set.", Log::ERROR_BUFFER);		
		//Powerup1
		/* TODO: Additional pUgradeBuilding check */
		if (it->powerupOne != "None" && it->powerupCount < 1)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has Powerup #1 set while count is lower than 1.", Log::WARNING);
		//Powerup2
		if (it->powerupTwo != "None" && it->powerupCount < 2)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has Powerup #2 set while count is lower than 2.", Log::WARNING);
		//Powerup2
		if (it->powerupThree != "None" && it->powerupCount < 3)
			Log::validatorLine("Structure at index '" + Log::toString(index) + "' has Powerup #3 set while count is lower than 3.", Log::WARNING);

		index++;
	}
}