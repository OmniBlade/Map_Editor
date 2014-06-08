#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class ScriptType;
class TaskForce;
class House;
class Country;
class Waypoint;
class INIFile;
class Tag;

class TeamType
{
public:
	static ObjectList<TeamType> Array;

	TeamType(const std::string& id);
	void parse(INIFile* file, bool isGlobal = false);
	std::string ID, Name, tag, owner, taskForce, script, waypoint, transWaypoint;
	
	House* houseOwner; //SP!
	Country* countryOwner; //MP!
	Tag* pTag;
	Waypoint* pWaypoint;
	Waypoint* pTransportWaypoint;
	TaskForce* pTaskForce;
	ScriptType* pScriptType;

	int VeteranLevel;
	int MindControlDecision;
	int Priority;
	int Max;
	int TechLevel;
	int Group;

	bool Loadable;
	bool Full;
	bool Annoyance;
	bool GuardSlower;
	bool Recruiter;
	bool Autocreate;
	bool Prebuild;
	bool Reinforce;
	bool Droppod;
	bool UseTransportOrigin;
	bool Whiner;
	bool LooseRecruit;
	bool Agressive;
	bool Suicide;
	bool OnTransOnly;
	bool AvoidThreats;
	bool IonImmune; //TS only
	bool TransportsReturnOnUnload;
	bool AreTeamMembersRecruitable;
	bool IsBaseDefense;
	bool OnlyTargetHouseEnemy;
	bool isGlobal;
};

