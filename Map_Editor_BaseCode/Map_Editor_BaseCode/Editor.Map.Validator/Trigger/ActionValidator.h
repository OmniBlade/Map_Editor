#pragma once
#include <string>

class Action;
class SubAction;
class ActionType;
class ParamType;

class ActionValidator
{
public:
	ActionValidator(const std::string& actionID, const std::string& tagID);
	~ActionValidator();

	void validate();
	void validateSubAction(SubAction* pAction, unsigned int number);
	bool waypointIsValid(SubAction* pAction, unsigned int number);
	bool paramIsGenericNumber(ParamType* type);
	bool itemExistsInList(SubAction* pAction, unsigned int index);
	bool genericNumberAboveZero(int value);
	bool attachedTagIsValid(ActionType* type);
	bool existsInCellTag();

private:
	std::string ID, tagID;
	Action* pAction;
};
