#include "stdafx.h"
#include "TeamType.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"
#include "../../../GameDefinition.h"
#include "ScriptType.hpp"
#include "TaskForce.hpp"
#include "../House.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Waypoint.hpp"
#include "../Triggers/Tag.hpp"

/* static */ ObjectList<TeamType> TeamType::Array;

TeamType::TeamType(const std::string& id)
:ID(id)
{
}

void TeamType::parse(INIFile* file, bool isGlobal_)
{
	INISection* section = file->getSection(ID);

	if (!section)
	{
		return;
	}

	isGlobal = isGlobal_;
	section->readStringValue("Name", Name);
	section->readStringValue("Tag", tag);
	section->readStringValue("House", owner);
	section->readStringValue("Script", script);
	section->readStringValue("TaskForce", taskForce);
	section->readStringValue("Waypoint", waypoint);
	section->readStringValue("TransportWaypoint", transWaypoint);

	section->readIntValue("VeteranLevel", VeteranLevel);
	
	if (Game::title == Game::Type::Expansion)
		section->readIntValue("MindControlDecision", MindControlDecision);
	
	section->readIntValue("Priority", Priority);
	section->readIntValue("Max", Max);
	section->readIntValue("TechLevel", TechLevel);
	section->readIntValue("Group", Group);

	section->readBoolValue("Loadable", Loadable);
	section->readBoolValue("Full", Full);
	section->readBoolValue("Annoyance", Annoyance);
	section->readBoolValue("GuardSlower", GuardSlower);
	section->readBoolValue("Recruiter", Recruiter);
	section->readBoolValue("Autocreate", Autocreate);
	section->readBoolValue("Prebuild", Prebuild);
	section->readBoolValue("Reinforce", Reinforce);
	section->readBoolValue("Droppod", Droppod);
	section->readBoolValue("UseTransportOrigin", UseTransportOrigin);
	section->readBoolValue("Whiner", Whiner);
	section->readBoolValue("LooseRecruit", LooseRecruit);
	section->readBoolValue("Agressive", Agressive);
	section->readBoolValue("Suicide", Suicide);
	section->readBoolValue("Loadable", Loadable);
	section->readBoolValue("OnTransOnly", OnTransOnly);
	section->readBoolValue("AvoidThreats", AvoidThreats);
	section->readBoolValue("IonImmune", IonImmune);
	section->readBoolValue("TransportsReturnOnUnload", TransportsReturnOnUnload);
	section->readBoolValue("AreTeamMembersRecruitable", AreTeamMembersRecruitable);
	section->readBoolValue("IsBaseDefense", IsBaseDefense);
	section->readBoolValue("OnlyTargetHouseEnemy", OnlyTargetHouseEnemy);

	/*
		Easy does it
		nullptr means the attached type is invalid
		This is used mainly to determine shit in the validator engine (nullptr for taskforce means no taskforce thus error)
		Oh, minor detail; crash if not checked for emptyness first!
	*/
	if (!owner.empty())
	{
		houseOwner = House::Array.find(owner);
		countryOwner = Country::Array.find(owner);
	}
	if (!tag.empty())
	{
		pTag = Tag::Array.find(tag);
	}
	if (section->checkKeyExistance("TaskForce"))
	{
		pTaskForce = TaskForce::Array.find(taskForce);
	}
	if (section->checkKeyExistance("Script"))
	{
		pScriptType = ScriptType::Array.find(script);
	}
	if (!waypoint.empty())
	{
		pWaypoint = Waypoint::Array.find(waypoint);
	}
	if (!transWaypoint.empty())
	{
		pTransportWaypoint = Waypoint::Array.find(transWaypoint);
	}
}
