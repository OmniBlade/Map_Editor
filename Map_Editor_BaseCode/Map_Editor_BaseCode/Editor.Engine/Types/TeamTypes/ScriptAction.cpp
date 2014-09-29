#include "stdafx.h"
#include "ScriptAction.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.FileSystem/MapFile/SActionType.hpp"
#include "../../../Editor.FileSystem/MapFile/SActionCollection.hpp"
#include "../../../Log.hpp"

ScriptAction::ScriptAction()
{

}

/* static */ std::shared_ptr<ScriptAction> ScriptAction::parse(LineSplitter& parts)
{
	auto ret = std::make_shared<ScriptAction>();


	if (parts.pop(ret->actionType))
	{
		ret->assignActionType();
		if (parts.pop(ret->parameter))
		{
			return ret;
		}
	}
	return nullptr;
}

void ScriptAction::assignActionType()
{
	pActionType = SActionCollection::getInstance()->get(actionType);
	if (!pActionType)
		Log::line("Unable to get ActionType for ScriptAction with ID " + Log::toString(actionType) + ".", Log::DEBUG);
}