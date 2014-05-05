#pragma once

#include <string>

class Tag;
class Action;
class Event;
class Country;

class Trigger
{
public:
	Trigger(const std::string& id, const std::string& list);
	void parse(const std::string& list);

	std::string ID, Name;
	bool Disabled;
	bool EasyEnabled;
	bool MedEnabled;
	bool HardEnabled;
	int Unknown;

	Country* owner;
	Trigger* child;
	Action* actionList;
	Event* eventList;
	
	/*
		This is pure for faster Trigger nesting, unlike FA2 which
		cannot even resolve the Tag of a parent Trigger without first
		having to click on that Trigger...
	*/
	Tag* attachedTag; 


};

