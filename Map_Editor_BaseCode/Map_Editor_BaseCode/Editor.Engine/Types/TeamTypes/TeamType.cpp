#include "stdafx.h"
#include "TeamType.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"
#include "ScriptType.hpp"
#include "TaskForce.hpp"
#include "../House.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Waypoint.hpp"

/* static */ ObjectList<TeamType> TeamType::Array;

TeamType::TeamType(const std::string& id)
:ID(id)
{
}

void TeamType::parse(INIFile* file)
{
	INISection* section = file->getSection(ID);

	section->readIntValue("VeteranLevel", VeteranLevel);
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
}
