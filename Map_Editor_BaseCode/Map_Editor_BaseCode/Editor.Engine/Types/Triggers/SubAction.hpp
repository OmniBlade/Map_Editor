#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../../../Editor.FileSystem/MapFile/ParamContent.h"

class ActionType;
class LineSplitter;

class SubAction
{
public:
	SubAction();
	static std::shared_ptr<SubAction> parse(LineSplitter& parts);
	static void parseTrivialParams(LineSplitter& parts, std::shared_ptr<SubAction> pAction);

	void assignActionType();

	int actionType = 0, parseType = 0;
	std::vector<ParamContent> params;

	ActionType* pActionType;
};

