#include "stdafx.h"
#include "TeamValidator.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp" 
#include "../../GameDefinition.h"
#include <algorithm>

//#include "../Editor.Engine/Types/House.hpp"
//#include "../Editor.Engine/Types/Waypoint.hpp"
//#include "../Editor.Engine/Types/Triggers/Tag.hpp"
#include "../../Editor.Engine/Types/TeamTypes/ScriptType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TaskForce.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TeamType.hpp"

TeamValidator::TeamValidator()
{
	//ScriptTypes
	validateScriptType();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//TaskForces
	validateTaskForce();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//TeamTypes
	validateTeamType();
	Log::finishErrorRound();
	Log::finishWarningRound();
}


TeamValidator::~TeamValidator()
{

}

void TeamValidator::validateScriptType()
{
	Log::validatorLine();
	Log::validatorLine("Validating [ScriptTypes] now...", Log::INFO);
	Log::validatorLine("Nothing to validate!", Log::CRITICAL);
	for (const auto& it : ScriptType::Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			if (it->actionList.size() > 50)
			{
				Log::validatorLine("ScriptType with ID '" + it->ID + "' has too many actions, game only parses the first 50.", Log::WARNING_BUFFER);
			}

			unsigned int index = 0;
			for (const auto& subIt : it->actionList)
			{
				if (index == 50)
					break;

				index++;
			}
		}
	}
}

void TeamValidator::validateTaskForce()
{
	Log::validatorLine();
	Log::validatorLine("Validating [TaskForces] now...", Log::INFO);
	for (const auto& it : TaskForce::Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			if (it->unitList.size() > 6)
			{
				Log::validatorLine("TaskForce with ID '" + it->ID + "' has too many units, game only parses the first 6.", Log::WARNING_BUFFER);
			}

			unsigned int index = 0;
			for (const auto& subIt : it->unitList)
			{
				if (index == 6)
					break;

				if (subIt->count < 1)
					Log::validatorLine("TaskForce with ID '" + it->ID + "' has an invalid Unit Count set for entry " + Log::toString(index+1)  + ".", Log::WARNING_BUFFER);
				if (!subIt->aircraft && !subIt->infantry && !subIt->vehicle)
					Log::validatorLine("TaskForce with ID '" + it->ID + "' has an invalid TechType set set for entry " + Log::toString(index+1) + ".", Log::ERROR_BUFFER);

				index++;
			}
		}
	}
}

void TeamValidator::validateTeamType()
{
	Log::validatorLine();
	Log::validatorLine("Validating [TeamTypes] now...", Log::INFO);
	for (const auto& it : TeamType::Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			if (!it->pTag && it->tag != "" && it->tag != "None")
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Tag set.", Log::ERROR_BUFFER);
			if (!it->countryOwner && (!Config::isSP && !validateMPOwner(it->owner)))
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Country as owner.", Log::ERROR_BUFFER);
			if (!it->pTaskForce && it->taskForce != "None" && !it->taskForce.empty())
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid TaskForce set.", Log::WARNING_BUFFER);
			if (!it->pScriptType && it->script != "None" && !it->script.empty())
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid ScriptType set.", Log::WARNING_BUFFER);
			if (!it->pWaypoint && !it->waypoint.empty())
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Waypoint set.", Log::ERROR_BUFFER);
			if (it->UseTransportOrigin && !it->pTransportWaypoint && !it->transWaypoint.empty())
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Transport Waypoint set.", Log::ERROR_BUFFER);
			if (it->VeteranLevel < 0 || it->VeteranLevel > 3)
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Veteran Level set.", Log::ERROR_BUFFER);
			if ((it->MindControlDecision < 0 || it->MindControlDecision > 5) && Game::title == Game::Type::Expansion)
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid Mind-Control Decision set.", Log::ERROR_BUFFER);
			if (it->TechLevel < 0 || it->TechLevel > 10)
				Log::validatorLine("TeamType with ID '" + it->ID + "' has an invalid TechLevel set.", Log::ERROR_BUFFER);
		}
	}
}

bool TeamValidator::validateMPOwner(const std::string& owner)
{
	if (mpCountries.empty())
	{
		mpCountries.push_back("<Player @ A>");
		mpCountries.push_back("<Player @ B>");
		mpCountries.push_back("<Player @ C>");
		mpCountries.push_back("<Player @ D>");
		mpCountries.push_back("<Player @ E>");
		mpCountries.push_back("<Player @ F>");
		mpCountries.push_back("<Player @ G>");
		mpCountries.push_back("<Player @ H>");
	}

	if (std::find(mpCountries.begin(), mpCountries.end(), owner) != mpCountries.end())
	{
		return true;
	}
	return false;
}