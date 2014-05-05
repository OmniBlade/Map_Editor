#pragma once

#include <string>

class ScriptType;
class TaskForce;
class House;
class Country;
class Waypoint;
class INIFile;

class TeamType
{
public:
	TeamType(const std::string& id);
	void parse(INIFile* file);
	std::string ID, Name;
	
	House* houseOwner; //SP!
	Country* countryOwner; //MP!
	//Tag* tag;
	Waypoint* waypoint;
	Waypoint* transportWaypoint;
	TaskForce* taskForce;
	ScriptType* scriptType;

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
};

