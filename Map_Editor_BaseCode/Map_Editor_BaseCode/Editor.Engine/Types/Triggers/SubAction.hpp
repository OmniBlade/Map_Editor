#pragma once
#include <string>
#include <memory>

class ActionType;
class LineSplitter;

class SubAction
{
public:
	SubAction();
	static std::shared_ptr<SubAction> parse(LineSplitter& parts);
	void assignActionType();

	int actionType, parseType, param1, param2, param3, param4, param5, param6;
	std::string param1S, param6S;

	ActionType* pActionType;
};

