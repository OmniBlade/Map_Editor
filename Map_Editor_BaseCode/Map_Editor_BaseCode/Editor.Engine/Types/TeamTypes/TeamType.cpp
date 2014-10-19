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
}

void TeamType::writeToINI(INIFile& file)
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
			it->writeContentToINI(file);
		}
	}
}

void TeamType::writeContentToINI(INIFile& file)
{
	file.SetValue(ID.c_str(), "Name", Name);
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
		file.SetValue(ID.c_str(), "Tag", pTag->ID);
	if (!waypoint.empty())
		file.SetValue(ID.c_str(), "Waypoint", pWaypoint->getLetterIndex());
	if (!transWaypoint.empty())
		file.SetValue(ID.c_str(), "TransportWaypoint", pTransportWaypoint->getLetterIndex());
	if (!script.empty())
		file.SetValue(ID.c_str(), "Script", pScriptType->ID);
	if (!taskForce.empty())
		file.SetValue(ID.c_str(), "TaskForce", pTaskForce->ID);

}