#pragma once
#include "IList.h"

/*
	True or False (basically 0 or 1) list
	- Used in Triggers
*/
class BoolList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "False / No", 0);
		add(items, "True / Yes", 1);

		return items;
	};
};

/*
	List of targeting types used by the game
	Name 'Quarry' comes from the game, taking over the name
	- Used in Triggers
	- Used in ScriptTypes
*/
class QuarryList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Nothing", 0);
		add(items, "Anything", 1);
		add(items, "Structures", 2);
		add(items, "Harvesters", 3);
		add(items, "Infantry", 4);
		add(items, "Vehicles", 5);
		add(items, "Factories", 6);
		add(items, "Base Defenses", 7);
		add(items, "Base Threats", 8);
		add(items, "Power Plants", 9);
		add(items, "Occupiable", 10);
		add(items, "Tech Buildings", 11);

		return items;
	};

};

/*
	Lists of camera speeds to move from point A to point B
	- Used in Triggers
	- Used in ScriptTypes
*/
class SpeedList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Very Slow", 0);
		add(items, "Slow", 1);
		add(items, "Medium", 2);
		add(items, "Fast", 3);
		add(items, "Very Fast", 4);

		return items;
	};
};

/*
	List of crates used by the game
	- Used in Triggers
*/
class CrateList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Money", 0);
		add(items, "Unit", 1);
		add(items, "Heal Base", 2);
		add(items, "Cloak", 3);
		add(items, "Explosion", 4);
		add(items, "Napalm", 5);
		add(items, "Squad (not working)", 6);
		add(items, "Darkness", 7);
		add(items, "Reveal", 8);
		add(items, "Armor", 9);
		add(items, "Speed", 10);
		add(items, "Firepower", 11);
		add(items, "ICBM", 12);
		add(items, "Invulnerability (not working)", 13);
		add(items, "Veteran", 14);
		add(items, "IonStorm (not working)", 15);
		add(items, "Gas", 16);
		add(items, "Tiberium", 17);
		add(items, "Pod (not working)", 18);

		return items;
	};

};

/*
	Speech bubble lists to display above units
	- Used in Triggers
	- Used in ScriptTypes
*/
class SBubbleList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "None", 0);
		add(items, "Asterisk (*)", 1);
		add(items, "Question mark (?)", 2);
		add(items, "Exclamation mark (!)", 3);

		return items;
	};
};

/*
	The list of spotlight behavior types
	WARNING: IT IS UNKNOWN WHETER OPTION 3 (FOLLOW) WORKS ON MAP OBJECTS
	- Used in Triggers
	- Used in Map Objects
*/
class LBehaviorList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "No spotlight", 0);
		add(items, "Sweep", 1);
		add(items, "Circle", 2);
		add(items, "Follow", 3);

		return items;
	};

};

/*
	The list of possible radar events used by the game
	- Used in Triggers
*/
class REventList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Combat", 0);
		add(items, "Non-Combat", 1);
		add(items, "Drop Zone", 2);
		add(items, "Base Attacked", 3);
		add(items, "Harvester Attacked", 4);
		add(items, "Enemy Sensed", 5);
		add(items, "Unit Produced", 6);
		add(items, "Unit Lost", 7);
		add(items, "Unit Repaired", 8);
		add(items, "Building Infiltrated", 9);
		add(items, "Building Captured", 10);
		add(items, "Beacon Placed", 11);
		add(items, "Superweapon Detected", 12);
		add(items, "Superweapon Activated", 13);
		add(items, "Bridge Repaired", 14);
		add(items, "Garrison Abandoned", 15);
		add(items, "Ally Base Attacked", 16);

		return items;
	};
};

/*
	The list of possible meteor shower sizes
	- Used in Triggers
*/
class ShowerList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "0 to 2 meteors", 0);
		add(items, "4 to 6 meteors", 1);
		add(items, "8 to 10 meteors", 2);
		add(items, "14 to 16 meteors", 3);
		add(items, "0 to 1 meteor", 4);

		return items;
	};
};

/*
	The list with the tabs used in RA2 and YR
	- Used in Triggers
*/
class TabList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Structures", 0);
		add(items, "Defenses", 1);
		add(items, "Infantry", 2);
		add(items, "Units", 3);

		return items;
	};
};

/*
	Mission list for units / infantry
	- Used in ScriptTypes
	- Used in Map Objects
*/
class MissionList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Sleep", 0);
		add(items, "Attack nearest enemy", 1);
		add(items, "Move", 2);
		add(items, "QMove", 3);
		add(items, "Retreat home for R&R", 4);
		add(items, "Guard", 5);
		add(items, "Sticky (never recruit)", 6);
		add(items, "Enter object", 7);
		add(items, "Capture object", 8);
		add(items, "Move into and get eaten", 9);
		add(items, "Harvest", 10);
		add(items, "Area Guard", 11);
		add(items, "Return (to refinery)", 12);
		add(items, "Stop", 13);
		add(items, "Ambush (wait until discovered)", 14);
		add(items, "Hunt", 15);
		add(items, "Unload", 16);
		add(items, "Sabotage (move in and destroy)", 17);
		add(items, "Construction", 18);
		add(items, "Deconstruction", 19);
		add(items, "Repair", 20);
		add(items, "Rescue", 21);
		add(items, "Missile", 22);
		add(items, "Harmless", 23);
		add(items, "Open", 24);
		add(items, "Patrol", 25);
		add(items, "Paradrop approach drop zone", 26);
		add(items, "Paradrop overfly drop zone", 27);
		add(items, "Wait", 28);
		add(items, "Attack again", 29);
		add(items, "Spyplane approach", 30);
		add(items, "Spyplane overfly", 31);

		return items;
	}
};

/*
	The list of possible facings
	- Used in ScriptTypes
	- Used in Map Objects
*/
class FacingList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "North", 0);
		add(items, "North East", 1);
		add(items, "East", 2);
		add(items, "South East", 3);
		add(items, "South", 4);
		add(items, "South West", 5);
		add(items, "West", 6);
		add(items, "North West", 7);

		return items;
	};
};

/*
	The list used for splitting transports and units
	- Used in ScriptTypes
*/
class SplitList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Keep Transports, Keep Units", 0);
		add(items, "Keep Transports, Lose Units", 1);
		add(items, "Lose Transports, Keep Units", 2);
		add(items, "Lose Transports, Lose Units", 3);

		return items;
	};

};

/*
	The TechLevel list used for Triggers
	WARNING: DO NOT USE FOR HOUSES BECAUSE OF -1 AND 11
	- Used in Triggers
*/
class TechLevelList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "-1 (Player cannot build this)", -1);
		add(items, "1", 1);
		add(items, "2", 2);
		add(items, "3", 3);
		add(items, "4", 4);
		add(items, "5", 5);
		add(items, "6", 6);
		add(items, "7", 7);
		add(items, "8", 8);
		add(items, "9", 9);
		add(items, "10", 10);
		add(items, "11 (Both AI and Player cannot build this)", 11);

		return items;
	};
};

/*
	The zoom list for zooming on the minimap
	- Used in Triggers
*/
class ZoomList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Normal", 1);
		add(items, "Zoomed out", 2);

		return items;
	};
};

/*
	The repeating list used by Tags (and probably the Trigger editor)
	- Used in Triggers
	- Used in Tags
*/
class RepeatList : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "Fire only once", 0);
		add(items, "Fire when all Events (attached to anything) are done", 1);
		add(items, "Repeating", 2);

		return items;
	};
};

/*
	The list for the conditions of AITriggerTypes
	- Used in AITriggerTypes
*/
class AICondition : public IList
{
public:
	List getList()
	{
		List items;

		add(items, "less than", 0);
		add(items, "less than or equal to", 1);
		add(items, "equal to", 2);
		add(items, "greater than or equal to", 3);
		add(items, "greater than", 4);
		add(items, "not equal to", 5);

		return items;
	};
};
