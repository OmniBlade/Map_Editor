#pragma once
#include <string>
#include <memory>

class LineSplitter;
class SActionType;

class ScriptAction
{
public:
	ScriptAction();
	static std::shared_ptr<ScriptAction> parse(LineSplitter& parts);
	void assignActionType();
	std::string asString();

	int actionType, parameter;
	SActionType* pActionType;
};

