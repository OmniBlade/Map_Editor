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
#include "../../../Editor.FileSystem/MapFile/WriterHelper.h"

/* static */ MapObjectList<TeamType> TeamType::Array;

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
	section->readDeletableStringValue("Name", Name);
	section->readDeletableStringValue("Tag", tag);
	section->readDeletableStringValue("House", owner);
	section->readDeletableStringValue("Script", script);
	section->readDeletableStringValue("TaskForce", taskForce);
	section->readDeletableStringValue("Waypoint", waypoint);
	section->readDeletableStringValue("TransportWaypoint", transWaypoint);

	section->readDeletableIntValue("VeteranLevel", VeteranLevel);
	
	if (Game::title == Game::Type::Expansion)
		section->readDeletableIntValue("MindControlDecision", MindControlDecision);
	
	section->readDeletableIntValue("Priority", Priority);
	section->readDeletableIntValue("Max", Max);
	section->readDeletableIntValue("TechLevel", TechLevel);
	section->readDeletableIntValue("Group", Group);

	section->readDeletableBoolValue("Loadable", Loadable);
	section->readDeletableBoolValue("Full", Full);
	section->readDeletableBoolValue("Annoyance", Annoyance);
	section->readDeletableBoolValue("GuardSlower", GuardSlower);
	section->readDeletableBoolValue("Recruiter", Recruiter);
	section->readDeletableBoolValue("Autocreate", Autocreate);
	section->readDeletableBoolValue("Prebuild", Prebuild);
	section->readDeletableBoolValue("Reinforce", Reinforce);
	section->readDeletableBoolValue("Droppod", Droppod);
	section->readDeletableBoolValue("UseTransportOrigin", UseTransportOrigin);
	section->readDeletableBoolValue("Whiner", Whiner);
	section->readDeletableBoolValue("LooseRecruit", LooseRecruit);
	section->readDeletableBoolValue("Aggressive", Agressive);
	section->readDeletableBoolValue("Suicide", Suicide);
	section->readDeletableBoolValue("Loadable", Loadable);
	section->readDeletableBoolValue("OnTransOnly", OnTransOnly);
	section->readDeletableBoolValue("AvoidThreats", AvoidThreats);
	section->readDeletableBoolValue("IonImmune", IonImmune);
	section->readDeletableBoolValue("TransportsReturnOnUnload", TransportsReturnOnUnload);
	section->readDeletableBoolValue("AreTeamMembersRecruitable", AreTeamMembersRecruitable);
	section->readDeletableBoolValue("IsBaseDefense", IsBaseDefense);
	section->readDeletableBoolValue("OnlyTargetHouseEnemy", OnlyTargetHouseEnemy);

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
	if (section->keyExists("TaskForce"))
	{
		pTaskForce = TaskForce::Array.find(taskForce);
	}
	if (section->keyExists("Script"))
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

	if (!section->size())
	{
		file->deleteSection(ID.c_str());
	}
}

void TeamType::writeToINI(INIFile& file, bool flushNames /* = false */)
{
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		if (!it->isGlobal)
		{
			number << i;
			file.SetValue("TeamTypes", number.str(), it->ID);
			++i;
			number.str(std::string());
			it->writeContentToINI(file, flushNames);
		}
	}
}

void TeamType::writeContentToINI(INIFile& file, bool voidNames /* = false */)
{
	file.SetValue(ID.c_str(), "Name", voidNames ? "flush!" : Name);
	file.SetValue(ID.c_str(), "VeteranLevel", Log::toString(VeteranLevel));
	if(Game::title == Game::Type::Expansion) file.SetValue(ID.c_str(), "MindControlDecision", Log::toString(MindControlDecision));
	file.SetValue(ID.c_str(), "Loadable", BoolWriter::getBoolString(Loadable, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Full", BoolWriter::getBoolString(Full, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Annoyance", BoolWriter::getBoolString(Annoyance, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "GuardSlower", BoolWriter::getBoolString(GuardSlower, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "House", owner);
	file.SetValue(ID.c_str(), "Recruiter", BoolWriter::getBoolString(Recruiter, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Autocreate", BoolWriter::getBoolString(Autocreate, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Prebuild", BoolWriter::getBoolString(Prebuild, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Reinforce", BoolWriter::getBoolString(Reinforce, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Droppod", BoolWriter::getBoolString(Droppod, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "UseTransportOrigin", BoolWriter::getBoolString(UseTransportOrigin, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Whiner", BoolWriter::getBoolString(Whiner, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "LooseRecruit", BoolWriter::getBoolString(LooseRecruit, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Agressive", BoolWriter::getBoolString(Agressive, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Suicide", BoolWriter::getBoolString(Suicide, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Priority", Log::toString(Priority));
	file.SetValue(ID.c_str(), "Max", Log::toString(Max));
	file.SetValue(ID.c_str(), "TechLevel", Log::toString(TechLevel));
	file.SetValue(ID.c_str(), "Group", Log::toString(Group));
	file.SetValue(ID.c_str(), "OnTransOnly", BoolWriter::getBoolString(OnTransOnly, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "AvoidThreats", BoolWriter::getBoolString(AvoidThreats, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "IonImmune", BoolWriter::getBoolString(IonImmune, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "TransportsReturnOnUnload", BoolWriter::getBoolString(TransportsReturnOnUnload, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "AreTeamMembersRecruitable", BoolWriter::getBoolString(AreTeamMembersRecruitable, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "IsBaseDefense", BoolWriter::getBoolString(IsBaseDefense, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "OnlyTargetHouseEnemy", BoolWriter::getBoolString(OnlyTargetHouseEnemy, BoolWriter::BoolType::YESNO));
	
	if (!tag.empty())
		file.SetValue(ID.c_str(), "Tag", pTag == nullptr ? tag : pTag->ID);
	if (!waypoint.empty())
		file.SetValue(ID.c_str(), "Waypoint", pWaypoint == nullptr ? waypoint : pWaypoint->getLetterIndex());
	if (!transWaypoint.empty())
		file.SetValue(ID.c_str(), "TransportWaypoint", pTransportWaypoint == nullptr ? transWaypoint : pTransportWaypoint->getLetterIndex());
	if (!script.empty())
		file.SetValue(ID.c_str(), "Script", pScriptType == nullptr ? script : pScriptType->ID);
	if (!taskForce.empty())
		file.SetValue(ID.c_str(), "TaskForce", pTaskForce == nullptr ? taskForce : pTaskForce->ID);

}