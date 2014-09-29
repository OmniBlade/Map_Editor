#include "stdafx.h"
#include "AIValidator.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"

#include "../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerEnable.hpp"

AIValidator::AIValidator()
{
	//AITriggers
	validateAITrigger();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Enables
	validateAIEnable();
	Log::finishErrorRound();
	Log::finishWarningRound();
}

AIValidator::~AIValidator()
{
}

void AIValidator::validateAITrigger()
{
	Log::validatorLine();
	Log::validatorLine("Validating [AITriggerTypes] now...", Log::INFO);
	for (const auto& it : AITriggerType::Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			//Owner
			if (!it->pCountry && it->owner != "<all>")
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Owner set.", Log::ERROR_BUFFER);
			//TeamTypes
			if (!it->teamtype1 && it->tt1 != "<none>")
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid TeamType 1 set.", Log::ERROR_BUFFER);
			if (!it->teamtype2 && it->tt2 != "<none>")
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid TeamType 2 set.", Log::ERROR_BUFFER);
			//TechLevel
			if (it->techlevel < 0 || it->techlevel > 10)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid TechLevel set.", Log::WARNING_BUFFER);
			//AITrigger
			if (it->aiTriggerType < -1 || it->aiTriggerType > 7)
			{
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Trigger Type set.", Log::ERROR_BUFFER);
			}
			else
			{
				//TechType's
				if (it->aiTriggerType == 0 || it->aiTriggerType == 1 || it->aiTriggerType == 7)
				{
					if (it->paramEquation < 0 || it->paramEquation > 6)
						Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Condition Type set.", Log::ERROR_BUFFER);
					if (it->paramNumber < 0)
						Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Condition Value set.", Log::ERROR_BUFFER);
					if (!checkTechType(it.get()))
						Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid TechType set.", Log::ERROR_BUFFER);
				}
				//Cash
				else if (it->aiTriggerType == 4)
				{
					if (it->paramEquation < 0 || it->paramEquation > 6)
						Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Condition Type set.", Log::ERROR_BUFFER);

					if (it->paramNumber < 0)
						Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Condition Value set.", Log::ERROR_BUFFER);
				}
			}
			//Weight
			if (it->weight < it->minWeight || it->weight > it->maxWeight)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Weight set.", Log::ERROR_BUFFER);
			if (it->minWeight < 0 || it->maxWeight)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Minimal Weight set.", Log::ERROR_BUFFER);
			if (it->maxWeight < 0 || it->maxWeight < it->minWeight)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Maximum Weight set.", Log::ERROR_BUFFER);
			//Skirmish
			if (!Config::isSP && !it->skirmish)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an Skirmish flag set to off, this is a multiplayer map.", Log::ERROR_BUFFER);
			//Side
			if (it->side < 0 || it->side > 3)
				Log::validatorLine("AITriggerType with ID '" + it->ID + "' has an invalid Side set.", Log::WARNING_BUFFER);
		}
	}
}

void AIValidator::validateAIEnable()
{
	Log::validatorLine();
	Log::validatorLine("Validating [AITriggerTypesEnable] now...", Log::INFO);
	for (const auto& it : AITriggerEnable::Array.objectTypeList)
	{
		if (!it->aiTrigger)
			Log::validatorLine("AITriggerEnable with ID '" + it->ID + "' has an invalid AITriggerType set.", Log::ERROR_BUFFER);
	}
}

bool AIValidator::checkTechType(AITriggerType* aiTrigger)
{
	if (!aiTrigger->pAircraftType && !aiTrigger->pBuildingType && !aiTrigger->pVehicleType && !aiTrigger->pInfantryType)
	{
		return false;
	}
	else
	{
		return true;
	}
}