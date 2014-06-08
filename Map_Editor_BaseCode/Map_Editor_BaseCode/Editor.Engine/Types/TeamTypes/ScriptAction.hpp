#pragma once
#include <string>
#include <memory>

class LineSplitter;
class SActionTemplate;

class ScriptAction
{
public:
	ScriptAction();
	static std::shared_ptr<ScriptAction> parse(LineSplitter& parts);
	void assignActionType();

	int actionType, parameter;
	SActionTemplate* pActionType;
};

