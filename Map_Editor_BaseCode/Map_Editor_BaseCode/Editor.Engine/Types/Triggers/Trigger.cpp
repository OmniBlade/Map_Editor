#include "stdafx.h"
#include "Trigger.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include "Tag.hpp"
#include "Action.hpp"
#include "Event.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"

/* static */ MapObjectList<Trigger> Trigger::Array;

Trigger::Trigger()
{
}

void Trigger::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);

	if (split.pop(owner) && split.pop(child) && split.pop(Name) && split.pop(Disabled) && split.pop(EasyEnabled)
		&& split.pop(MedEnabled) && split.pop(HardEnabled) && split.pop(Unknown))
	{
		pOwner = Country::Array.find(owner);
		pAction = Action::Array.find(ID);
		pEvent = Event::Array.find(ID);

		if (pEvent)
		{
			pEvent->parseEvents();
		}

		if (pAction)
		{
			pAction->parseActions();
		}
	}
	else
	{
		Log::line("Unable to parse Trigger with ID '" + ID + "'.", Log::DEBUG);
	}

}

void Trigger::assignChild()
{

	if (child != "<None>")
	{
		pChild = Trigger::Array.find(child);
	}
	assignTag();
}

void Trigger::assignTag()
{
	for (const auto& it : Tag::Array.objectTypeList)
	{
		if (it->trigger == ID)
		{
			pTag = it.get();
			break;
		}
	}
}

std::string Trigger::getUpperParentID()
{
	Trigger* current = this;
	while (true)
	{
		Trigger* currentFallBack = current;
		for (const auto& it : Trigger::Array.objectTypeList)
		{
			if (it->pChild == current)
			{
				current = it->pChild;
				break;
			}
		}

		if (current == currentFallBack)
		{
			return current->ID;
		}
	}

	return std::string();
}

std::string Trigger::getParentID()
{
	for (const auto& it : Trigger::Array.objectTypeList)
	{
		if (it->pChild == this)
		{
			return it->ID;
		}
	}
	return std::string();
}

std::string Trigger::asString()
{
	char buffer[512];
	sprintf_s(buffer, 512, "%s,%s,%s,%d,%d,%d,%d,%d",
		this->pOwner->ID.c_str(),
		this->child.c_str(),
		this->Name.c_str(),
		this->Disabled != 0,
		this->EasyEnabled != 0,
		this->MedEnabled != 0,
		this->HardEnabled != 0,
		this->Unknown
		);

	return buffer;

}