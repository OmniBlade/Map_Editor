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
		Log::line();
		Log::line("---- Map validation ----", Log::INFO);
		Log::line("The fewer lines below, the better.", Log::EXTRAS);
		Log::line("Lines marked with 'ERROR' should be fixed before launching the map. ", Log::EXTRAS);
		Log::line("Lines marked with 'WARNING' are worth checking out before launching the map. ", Log::EXTRAS);
		Log::line("Lines marked with 'INFO' are pure information lines, no real value unless applied to an entry. ", Log::EXTRAS);
		Log::line("Depending on the settings, types will be validated.", Log::EXTRAS);

		Log::line();
		Log::line("=== Aircraft / Infantry / Terrain / Units / Structures ===", Log::EXTRAS);
		ObjectValidator objectValidator;

		Log::line();
		Log::line("=== TeamTypes / ScriptTypes / TaskForces ===", Log::EXTRAS);
		TeamValidator teamValidator;

		Log::line();
		Log::line("=== AITriggerTypes / AITriggerTypesEnable ===", Log::EXTRAS);
		AIValidator aiValidator;
	
		Log::line();
		Log::line("=== Smudges / Tubes / Waypoints ===", Log::EXTRAS);
		MiscValidator miscValidator;

		Log::line();
		Log::line("=== Tags / CellTags / Triggers / Actions / Events ===", Log::EXTRAS);
		TriggerValidator triggerValidator;
	}

	MainValidator::~MainValidator()
	{
	}
};

