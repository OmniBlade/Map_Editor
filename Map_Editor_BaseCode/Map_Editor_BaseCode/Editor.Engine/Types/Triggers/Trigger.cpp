#include "stdafx.h"
#include "Trigger.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include "Tag.hpp"
#include "Action.hpp"
#include "Event.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"

/* static */ ObjectList<Trigger> Trigger::Array;

Trigger::Trigger()
{
}

void Trigger::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);

	std::string house = split.pop_string();
	std::string trigger = split.pop_string();
	Name = split.pop_string();
	Disabled = split.pop_bool();
	EasyEnabled = split.pop_bool();
	MedEnabled = split.pop_bool();
	HardEnabled = split.pop_bool();
	Unknown = split.pop_int();
}