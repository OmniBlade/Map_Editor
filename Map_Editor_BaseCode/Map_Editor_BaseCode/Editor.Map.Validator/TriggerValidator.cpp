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
	Log::validatorLine();
	Log::validatorLine("Validating [CellTags] now...", Log::INFO);
	for (const auto& it : CellTag::Array.objectTypeList)
	{
		if (it->loc.x < 0)
			Log::validatorLine("CellTag with ID / coords '" + it->Location + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		if (it->loc.y < 0)
			Log::validatorLine("CellTag with ID / coords '" + it->Location + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		if (!it->pTag)
			Log::validatorLine("CellTag with ID / coords '" + it->Location + "' has an invalid Tag set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateTags()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Tags] now...", Log::INFO);
	for (const auto& it : Tag::Array.objectTypeList)
	{
		if (it->Repeating < 0 || it->Repeating > 2)
			Log::validatorLine("Tag with ID '" + it->ID + "' has an invalid Repeating type set.", Log::ERROR_BUFFER);
		if (!it->pTrigger)
			Log::validatorLine("Tag with ID '" + it->ID + "' has an invalid Trigger set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateTriggers()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Triggers] now...", Log::INFO);
	for (const auto& it : Trigger::Array.objectTypeList)
	{
		if (!it->pOwner)
			Log::validatorLine("Trigger with ID '" + it->ID + "' has an invalid Owner set.", Log::ERROR_BUFFER);
		if (!it->pAction)
			Log::validatorLine("Trigger with ID '" + it->ID + "' has no corresponding Action list.", Log::WARNING_BUFFER);
		if (!it->pEvent)
			Log::validatorLine("Trigger with ID '" + it->ID + "' has no corresponding Event list.", Log::WARNING_BUFFER);
		if (!it->pChild && it->child != "<none>")
			Log::validatorLine("Trigger with ID '" + it->ID + "' has an invalid Attached Trigger set.", Log::ERROR_BUFFER);
	}
}

void TriggerValidator::validateActions()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Actions] now...", Log::INFO);
	Log::validatorLine("Nothing to validate!", Log::CRITICAL);
}

void TriggerValidator::validateEvents()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Events] now...", Log::INFO);
	Log::validatorLine("Nothing to validate!", Log::CRITICAL);
}