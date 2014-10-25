#include "stdafx.h"
#include "NameFlusherClass.h"
#include "../../IniFile/INIFile.hpp"
#include "../../IniFile/INISection.hpp"
#include "../../../Editor.Engine/Types/VariableName.hpp"
#include "../../../Editor.Engine/Types/TeamTypes/ScriptType.hpp"
#include "../../../Editor.Engine/Types/TeamTypes/TaskForce.hpp"
#include "../../../Editor.Engine/Types/TeamTypes/TeamType.hpp"
#include "../../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../../Editor.Engine/Types/Triggers/Trigger.hpp"
#include "../../../Editor.Engine/Types/Triggers/Tag.hpp"

NameFlusherClass::NameFlusherClass()
{
}


NameFlusherClass::~NameFlusherClass()
{
}

/* static */ void NameFlusherClass::readAndRestoreFrom(INIFile& namesFile)
{
	auto pVariables = namesFile.getSection("VariableNames");
	if (pVariables)
		restoreBySection(*pVariables, VariableName::Array);
	auto pScriptTypes = namesFile.getSection("ScriptTypes");
	if (pScriptTypes)
		restoreBySection(*pScriptTypes, ScriptType::Array);
	auto pTaskForces = namesFile.getSection("TaskForces");
	if (pTaskForces)
		restoreBySection(*pTaskForces, TaskForce::Array);
	auto pTeamTypes = namesFile.getSection("TeamTypes");
	if (pTeamTypes)
		restoreBySection(*pTeamTypes, TeamType::Array);
	auto pAITriggers = namesFile.getSection("AITriggerTypes");
	if (pAITriggers)
		restoreBySection(*pAITriggers, AITriggerType::Array);
	auto pTriggers = namesFile.getSection("Triggers");
	if (pTriggers)
		restoreBySection(*pTriggers, Trigger::Array);
	auto pTags = namesFile.getSection("Tags");
	if (pTags)
		restoreBySection(*pTags, Tag::Array);
}

/* static */ void NameFlusherClass::writeToFile(INIFile& namesFile)
{
	writeByType(namesFile, VariableName::Array, "VariableNames");
	writeByType(namesFile, ScriptType::Array, "ScriptTypes");
	writeByType(namesFile, TaskForce::Array, "TaskForces");
	writeByType(namesFile, TeamType::Array, "TeamTypes");
	writeByType(namesFile, AITriggerType::Array, "AITriggerTypes");
	writeByType(namesFile, Trigger::Array, "Triggers");
	writeByType(namesFile, Tag::Array, "Tags");
}