#pragma once
#include <string>

class Event;
class SubEvent;
class EventType;
class ParamType;

struct ParamContent;

class EventValidator
{
public:
	enum ParseType
	{
		IsIndex = 0,
		IsID = 1,
	};

	EventValidator(const std::string& eventID, const std::string& tagID);
	~EventValidator();

	void validate();
	void validateSubEvent(unsigned int number);
	bool isID(int p1);
	bool isTechnoType(int p1);
	bool isIndex(int p1);
	//Validation of param
	void validateNumberParam(unsigned int number);
	void validateIDParam(unsigned int number);
	void validateTechnoParam(unsigned int number);
	bool tagIsValid();
	bool paramIsGenericNumber(ParamType* type);
	bool itemExistsInList(unsigned int index, ParseType type, ParamContent& paramToCheck);
	bool genericNumberAboveZero(int value);
	bool attachedTagIsValid();
	bool existsInCellTag();

private:
	unsigned int atSubEvent = 0;
	std::string ID, tagID;
	Event* pEvent;
	SubEvent* pSubEvent;
	EventType* pEventType;
};

