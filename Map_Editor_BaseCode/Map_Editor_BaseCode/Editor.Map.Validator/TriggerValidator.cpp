#include "stdafx.h"
#include "TriggerValidator.hpp"
#include "../Log.hpp"
#include "../Config.hpp"

#include "../Editor.Engine/Types/Triggers/Action.hpp"
#include "../Editor.Engine/Types/Triggers/Event.hpp"
#include "../Editor.Engine/Types/Triggers/CellTag.hpp"
#include "../Editor.Engine/Types/Triggers/Tag.hpp"
#include "../Editor.Engine/Types/Triggers/Trigger.hpp"

TriggerValidator::TriggerValidator()
{
	//Tags
	validateTags();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//CellTags
	validateCellTags();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Triggers
	validateTriggers();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Events
	validateEvents();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Actions
	validateActions();
	Log::finishErrorRound();
	Log::finishWarningRound();
}

TriggerValidator::~TriggerValidator()
{
}

void TriggerValidator::validateCellTags()
{
	Log::line();
	Log::line("Validating [CellTags] now...", Log::INFO);
	for (const auto& it : CellTag::Array.objectTypeList)
	{
		if (it->loc.x < 0)
			Log::line("CellTag with ID / coords '" + it->Location + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		if (it->loc.y < 0)
			Log::line("CellTag with ID / coords '" + it->Location + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		if (!it->pTag)
			Log::line("CellTag with ID / coords '" + it->Location + "' has an invalid Tag set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateTags()
{
	Log::line();
	Log::line("Validating [Tags] now...", Log::INFO);
	for (const auto& it : Tag::Array.objectTypeList)
	{
		if (it->Repeating < 0 || it->Repeating > 2)
			Log::line("Tag with ID '" + it->ID + "' has an invalid Repeating type set.", Log::ERROR_BUFFER);
		if (!it->pTrigger)
			Log::line("Tag with ID '" + it->ID + "' has an invalid Trigger set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateTriggers()
{
	Log::line();
	Log::line("Validating [Triggers] now...", Log::INFO);
	for (const auto& it : Trigger::Array.objectTypeList)
	{
		if (!it->pOwner)
			Log::line("Trigger with ID '" + it->ID + "' has an invalid Owner set.", Log::ERROR_BUFFER);
		if (!it->pAction)
			Log::line("Trigger with ID '" + it->ID + "' has no corresponding Action list.", Log::WARNING_BUFFER);
		if (!it->pEvent)
			Log::line("Trigger with ID '" + it->ID + "' has no corresponding Event list.", Log::WARNING_BUFFER);
		if (!it->pChild && it->child != "<none>")
			Log::line("Trigger with ID '" + it->ID + "' has an invalid Attached Trigger set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateActions()
{
	Log::line();
	Log::line("Validating [Actions] now...", Log::INFO);
	Log::line("Nothing to validate!", Log::CRITICAL);
}

void TriggerValidator::validateEvents()
{
	Log::line();
	Log::line("Validating [Events] now...", Log::INFO);
	Log::line("Nothing to validate!", Log::CRITICAL);
}