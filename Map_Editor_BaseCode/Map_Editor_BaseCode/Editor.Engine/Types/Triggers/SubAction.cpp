#include "stdafx.h"
#include "SubAction.hpp"
#include "../../../Editor.FileSystem/MapFile/ActionCollection.hpp"
#include "../../../Editor.FileSystem/MapFile/ActionType.hpp"
#include "../../../Log.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

SubAction::SubAction()
: actionType(-1), parseType(-1)
{

}

/* static */ std::shared_ptr<SubAction> SubAction::parse(LineSplitter& parts)
{
	auto ret = std::make_shared<SubAction>();

	/*
		Okay, I guess this is it, based on P1 stuff is parsed as text (ID) or number (Index)
		It is shit, but then again, so was Westwood's implementation
	*/
	if (parts.pop(ret->actionType) && parts.pop(ret->parseType))
	{
		ret->assignActionType();
		ret->params.resize(6);
		ret->params.reserve(6);

		switch (ret->parseType)
		{
		default:
		case 0: // Number, String
			parts.pop(ret->params[0].Index);
			parseTrivialParams(parts, ret);
			parts.pop(ret->params[5].ID);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 6:
		case 7:
		case 8:
		case 10: // String, String
			parts.pop(ret->params[0].ID);
			parseTrivialParams(parts, ret);
			parts.pop(ret->params[5].ID);
			break;
		case 5:
		case 9: // String, Number
			parts.pop(ret->params[0].ID);
			parseTrivialParams(parts, ret);
			parts.pop(ret->params[5].Index);
			break;
		case 11: // Number, Number
			parts.pop(ret->params[0].Index);
			parseTrivialParams(parts, ret);
			parts.pop(ret->params[5].Index);
			break;
		}
		return ret;
	}

	return nullptr;
}

/* static */ void SubAction::parseTrivialParams(LineSplitter& parts, std::shared_ptr<SubAction> pAction)
{
	for (unsigned int i = 1; i < 5; ++i)
	{
		parts.pop(pAction->params[i].Index);
	}
}

void SubAction::assignActionType()
{
	pActionType = ActionCollection::getInstance()->get(actionType);
	if (!pActionType)
		Log::line("Unable to get ActionType for SubAction with ID " + Log::toString(actionType) + ".", Log::DEBUG);
}

std::string SubAction::asString()
{
	char buffer[512];
	sprintf_s(buffer, 512, ",%d,%d,%s,%d,%d,%d,%d,%s",
		this->actionType,
		this->parseType,
		paramAsString(0).c_str(),
		this->params[1].Index,
		this->params[2].Index,
		this->params[3].Index,
		this->params[4].Index,
		paramAsString(5).c_str()
		);

	return buffer;
}

std::string SubAction::paramAsString(int paramNumber)
{
	std::string ret;

	if (params[paramNumber].ID.empty())
	{
		ret = Log::toString(params[paramNumber].Index);
	}
	else
	{
		ret = params[paramNumber].ID;
	}

	return ret;
}