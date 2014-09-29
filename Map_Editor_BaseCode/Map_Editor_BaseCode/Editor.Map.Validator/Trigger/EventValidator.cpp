#include "stdafx.h"
#include "EventValidator.h"
#include "../../Log.hpp"
#include "../../Editor.Engine/Types/Triggers/Event.hpp"
#include "../../Editor.Engine/Types/Triggers/SubEvent.hpp"
#include "../../Editor.FileSystem/MapFile/EventType.hpp"
#include "../../Editor.FileSystem/MapFile/ParamType.hpp"
#include "../../Editor.Engine/Types/Triggers/CellTag.hpp"
#include "../../Editor.Engine/Types/Triggers/Tag.hpp"
#include "../../Editor.FileSystem/MapFile/ParamContent.h"
#include "../../Editor.Engine/Lists/ListProvider.h"

#include <iostream>

EventValidator::EventValidator(const std::string& eventID, const std::string& tagID_)
:ID(eventID), tagID(tagID_)
{
	validate();
}


EventValidator::~EventValidator()
{

}

void EventValidator::validate()
{
	pEvent = Event::Array.find(ID);

	if (!pEvent)
	{
		Log::validatorLine("Event with ID '" + ID + "' does not exist!", Log::WARNING_BUFFER);
	}

	unsigned int number = 0;
	for (auto& it : pEvent->eventList)
	{
		number++;
		pSubEvent = it.get();
		validateSubEvent(number);
	}
}

void EventValidator::validateSubEvent(unsigned int number)
{
	pEventType = pSubEvent->pEventType;

	if (isIndex(pEventType->P1))
	{
		//NUMBER
		validateNumberParam(number);
	}
	else if (isID(pEventType->P1))
	{
		//STRING
		validateIDParam(number);
	}
	else if (isTechnoType(pEventType->P1))
	{
		//STRING + NUMBER
		validateTechnoParam(number);
	}
	else
	{
		//Log error
		Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + " has no valid parse type set!", Log::ERROR_BUFFER);
	}

//	atSubEvent++;

	if (pSubEvent->pEventType->tagCode == "C")
	{
		if (!existsInCellTag())
		{
			Log::validatorLine("Event with #" + Log::toString(number) + " from ID '" + ID + "' does not exist in a Cell-Tag!", Log::WARNING_BUFFER);
		}
	}
}

bool EventValidator::isID(int p1)
{
	return p1 == -1 ? true : false;
}

bool EventValidator::isIndex(int p1)
{
	return p1 == 0 ? true : false;
}

bool EventValidator::isTechnoType(int p1)
{
	return p1 == -2 ? true : false;
}

void EventValidator::validateNumberParam(unsigned int number)
{
	if (pEventType->paramList[1]->listIndex != 0) // P2's list is 0, no list
	{
		std::vector<ListItem> list = ListProvider::getProvider()->getListFor(pEventType->paramList[1]->listIndex);
		
		for (const auto& it : list)
		{
			if (it.Index == pSubEvent->params[0].Index)
			{
				if (!it.valid)
				{
					Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + "' references an invalid entry '" + it.ID +"'!", Log::WARNING_BUFFER);
				}
				else
				{
					return;
				}
			}
		}

		if (pSubEvent->params[0].Index > list.size())
		{
			Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + "' has an invalid value set!", Log::ERROR_BUFFER);
		}
	}
	else if (pSubEvent->params[0].Index < 0)
	{
		Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + "' has a negative value set!", Log::ERROR_BUFFER);
	}
}

void EventValidator::validateIDParam(unsigned int number)
{
	if (pEventType->paramList[1]->listIndex != 0) // P2's list is 0, no list
	{
		std::vector<ListItem> list = ListProvider::getProvider()->getListFor(pEventType->paramList[1]->listIndex);

		for (const auto& it : list)
		{
			if (it.ID == pSubEvent->params[atSubEvent].ID)
				return;
		}

		Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + " has an invalid value set!", Log::ERROR_BUFFER);
	}
}

void EventValidator::validateTechnoParam(unsigned int number)
{
	if (pEventType->paramList[1]->listIndex != 0) // P2's list is 0, no list
	{
		std::vector<ListItem> list = ListProvider::getProvider()->getListFor(pEventType->paramList[1]->listIndex);

		for (const auto& it : list)
		{
			if (it.ID == pSubEvent->params[0].ID)
				return;
		}

		Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + " has an invalid value set!", Log::ERROR_BUFFER);
	}

	if (pEventType->paramList[2]->listIndex < 0) // P2's list is 0, no list
	{
			Log::validatorLine("Event #" + Log::toString(number) + " from Trigger with ID '" + ID + " has an invalid number set!", Log::ERROR_BUFFER);
	}

	
}

bool EventValidator::paramIsGenericNumber(ParamType* type)
{
	if (type->paramID > 0)
	{
		return true;
	}
	return false;
}

bool EventValidator::itemExistsInList(unsigned int index, ParseType type, ParamContent& paramToCheck)
{
	std::vector<ListItem> list = ListProvider::getProvider()->getListFor(index);

	switch (type)
	{
	case (ParseType::IsIndex) :
		for (auto& it : list)
		{
		if (it.Index == paramToCheck.Index)
			return true;
		}
		break;
	case(ParseType::IsID) :
	default:
		for (auto& it : list)
		{
			if (it.ID == paramToCheck.ID)
				return true;
		}
		break;
	}
	return false;
}

bool EventValidator::genericNumberAboveZero(int value)
{
	if (value >= 0)
		return true;

	return false;
}

bool EventValidator::tagIsValid()
{
	return false;
}

bool EventValidator::existsInCellTag()
{
	Tag* pTag = nullptr;
	for (auto& it : Tag::Array.objectTypeList)
	{
		if (it->ID == tagID)
		{
			pTag = it.get();
			break;
		}
	}

	if (!pTag)
	{
		return false;
	}


	for (auto& it : CellTag::Array.objectTypeList)
	{
		if (it->pTag == pTag)
		{
			return true;
		}
	}


	return false;
}