#pragma once
#include "stdafx.h"
#include "MainValidator.hpp"
#include "ObjectValidator.hpp"
#include "TeamValidator.hpp"
#include "AIValidator.hpp"
#include "MiscValidator.hpp"
#include "TriggerValidator.hpp"
#include "../Log.hpp"
#include "../Config.hpp"

class MainValidator
{
public:
	MainValidator::MainValidator()
	{
		Log::validatorLine();
		Log::validatorLine("---- Map validation ----", Log::INFO);
		Log::validatorLine("The fewer lines below, the better.", Log::EXTRAS);
		Log::validatorLine("Lines marked with 'ERROR' should be fixed before launching the map. ", Log::EXTRAS);
		Log::validatorLine("Lines marked with 'WARNING' are worth checking out before launching the map. ", Log::EXTRAS);
		Log::validatorLine("Lines marked with 'INFO' are pure information lines, no real value unless applied to an entry. ", Log::EXTRAS);
		Log::validatorLine("Depending on the settings, types will be validated.", Log::EXTRAS);

		Log::validatorLine();
		Log::validatorLine("=== Aircraft / Infantry / Terrain / Units / Structures ===", Log::EXTRAS);
		ObjectValidator objectValidator;

		Log::validatorLine();
		Log::validatorLine("=== TeamTypes / ScriptTypes / TaskForces ===", Log::EXTRAS);
		TeamValidator teamValidator;

		Log::validatorLine();
		Log::validatorLine("=== AITriggerTypes / AITriggerTypesEnable ===", Log::EXTRAS);
		AIValidator aiValidator;
	
		Log::validatorLine();
		Log::validatorLine("=== Smudges / Tubes / Waypoints ===", Log::EXTRAS);
		MiscValidator miscValidator;

		Log::validatorLine();
		Log::validatorLine("=== Tags / CellTags / Triggers / Actions / Events ===", Log::EXTRAS);
		TriggerValidator triggerValidator;
	}

	MainValidator::~MainValidator()
	{
	}
};

