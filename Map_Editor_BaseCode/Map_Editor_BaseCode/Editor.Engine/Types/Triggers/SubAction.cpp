#include "stdafx.h"
#include "SubAction.hpp"
#include "../../../Editor.FileSystem/MapFile/ActionCollection.hpp"
#include "../../../Editor.FileSystem/MapFile/ActionTemplate.hpp"
#include "../../../Log.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

SubAction::SubAction()
: actionType(-1), parseType(-1)
{

}

/* static */ std::shared_ptr<SubAction> SubAction::parse(LineSplitter& parts)
{
	auto ret = std::make_shared<SubAction>();


	if (parts.pop(ret->actionType) && parts.pop(ret->parseType))
	{
		if (parts.pop(ret->param1S) && parts.pop(ret->param2) && parts.pop(ret->param3) && parts.pop(ret->param4)
			&& parts.pop(ret->param5) && parts.pop(ret->param6S))
		{
			return ret;
		}
	}
	return nullptr;
}

void SubAction::assignActionType()
{
	pActionType = ActionCollection::getInstance()->get(actionType);
	if (!pActionType)
		Log::note("Unable to get ActionType for SubAction with ID " + Log::toString(actionType) + ".", Log::DEBUG);
}