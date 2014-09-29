#include "stdafx.h"
#include "ActionValidator.h"
#include "../../Log.hpp"
#include "../../Editor.Engine/Types/Triggers/Action.hpp"
#include "../../Editor.Engine/Types/Triggers/SuBaction.hpp"
#include "../../Editor.FileSystem/MapFile/ActionType.hpp"
#include "../../Editor.FileSystem/MapFile/ParamType.hpp"
#include "../../Editor.Engine/Types/Triggers/CellTag.hpp"
#include "../../Editor.Engine/Types/Triggers/Tag.hpp"
#include "../../Editor.Engine/Lists/ListProvider.h"

ActionValidator::ActionValidator(const std::string& eventID, const std::string& tagID_)
	:ID(eventID), tagID(tagID_)
{
	validate();
}


ActionValidator::~ActionValidator()
{

}

void ActionValidator::validate()
{
	pAction = Action::Array.find(ID);

	if (!pAction)
	{
		Log::validatorLine("Action with ID '" + ID + "' does not exist!", Log::WARNING_BUFFER);
	}

	unsigned int number = 0;
	for (auto& it : pAction->actionList)
	{
		number++;
		validateSubAction(it.get(), number);
	}
}

void ActionValidator::validateSubAction(SubAction* pSubAction, unsigned int number)
{
	ActionType* pActionType = pSubAction->pActionType;

	for (unsigned int i = 0; i < pActionType->paramList.size(); ++i)
	{
		if (pActionType->paramList[i])
		{
			if (paramIsGenericNumber(pActionType->paramList[i]))
			{
				//if (!genericNumberAboveZero(pSubAction->param1))
					Log::validatorLine("Action #" + Log::toString(number) + " from Trigger with ID '" + ID + "' has value set higher than 0!", Log::WARNING_BUFFER);
			}
		//	else if (!itemExistsInList(pSubAction, pActionType->paramList[i]->listIndex)) // || !waypointIsValid(pSubAction, pActionType->paramList.back()->listIndex))
		//	{
		//		Log::validatorLine("Action with #" + Log::toString(number) + " from ID '" + ID + "' has an invalid value set!", Log::WARNING);
		//	}
		}
	}

	if (pSubAction->pActionType->tagCode == "C")
	{
		if (!existsInCellTag())
		{
			Log::validatorLine("Action with #" + Log::toString(number) + " from ID '" + ID + "' does not exist in a Cell-Tag!", Log::WARNING_BUFFER);
		}
	}
}

bool ActionValidator::waypointIsValid(SubAction* pSubAction, unsigned int index)
{
	std::vector<ListItem> list = ListProvider::getProvider()->getListFor(index);
	ActionType* pActionType = pSubAction->pActionType;

	switch (pActionType->P1)
	{
	case(-5) :
	case(-9) :
	case(-11) :
			  if (!paramIsGenericNumber(pActionType->paramList.back()))
			  {
				for (auto& it : list)
				{
					//if (it.Index == pSubAction->param6)
						return true;
				}
				break;
			  }
			  else
			  {
				  //return genericNumberAboveZero(pSubAction->param6);
			  }
	default:
		for (auto& it : list)
		{
			//if (it.ID == pSubAction->param6S)
				return true;
		}
		break;
	}

	return false;

}


bool ActionValidator::paramIsGenericNumber(ParamType* type)
{
	if (type->paramID > 0)
	{
		return true;
	}
	return false;
}

bool ActionValidator::itemExistsInList(SubAction* pSubAction, unsigned int index)
{
	std::vector<ListItem> list = ListProvider::getProvider()->getListFor(index);
	ActionType* pActionType = pSubAction->pActionType;

	switch (pActionType->P1)
	{
	case (0) :
	case (-11) :
		for (auto& it : list)
		{
	//	if (it.Index == pSubAction->param1)
			return true;
		}
			 break;
	case(-1) :
	case(-2) :
	case(-3) :
	case(-4) :
	case(-5) :
	case(-6) :
	case(-7) :
	case(-8) :
	case(-9) :
	case(-10) :
	default:
		for (auto& it : list)
		{
	//	if (it.ID == pSubAction->param1S)
			return true;
		}
			 break;
	}

	return false;
}

bool ActionValidator::genericNumberAboveZero(int value)
{
	if (value >= 0)
		return true;

	return false;
}

bool ActionValidator::attachedTagIsValid(ActionType* type)
{
	return false;
}

bool ActionValidator::existsInCellTag()
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