#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Types/AI/AITriggerEnable.hpp"
#include "../Types/AI/AITriggerType.hpp"
#include "../Types/Objects/Aircraft.hpp"
#include "../Types/Objects/Structure.hpp"
#include "../Types/Objects/Unit.hpp"
#include "../Types/Objects/Infantry.hpp"
#include "../Types/Objects/Terrain.hpp"
#include "../Types/TeamTypes/ScriptType.hpp"
#include "../Types/TeamTypes/TaskForce.hpp"
#include "../Types/TeamTypes/TeamType.hpp"
#include "../Types/Triggers/CellTag.hpp"
#include "../Types/Triggers/Tag.hpp"
#include "../Types/Triggers/Trigger.hpp"
#include "../Types/Tube.hpp"
#include "../Types/Waypoint.hpp"
#include "../Types/VariableName.hpp"

/*
	This is the class that holds everything that is READ from the map file and
	WRITTEN to the map file upon saving.
*/
class Map
{
public:
	static Map* getInstance();
	/*
		Write all the content to the map file
	*/
	void writeAll();

	std::vector<std::unique_ptr<VariableName>> variableList;
	std::vector<std::unique_ptr<Trigger>> triggerList;
	std::vector<std::unique_ptr<Tag>> tagList;
	std::vector<std::unique_ptr<CellTag>> cellTagList;
	std::vector<std::unique_ptr<Waypoint>> waypointList;
	std::vector<std::unique_ptr<AITriggerType>> aiTriggerList;
	std::vector<std::unique_ptr<AITriggerEnable>> aiEnableList;
	std::vector<std::unique_ptr<TeamType>> teamTypeList;
	std::vector<std::unique_ptr<TaskForce>> taskforceList;
	std::vector<std::unique_ptr<ScriptType>> scripttypeList;
	std::vector<std::unique_ptr<Structure>> structureList;
	std::vector<std::unique_ptr<Infantry>> infantryList;
	std::vector<std::unique_ptr<Unit>> unitList;
	std::vector<std::unique_ptr<Aircraft>> aircraftList;
	std::vector<std::unique_ptr<Terrain>> terrainList;
	std::vector<std::unique_ptr<Tube>> tubeList;

private:
	Map();
	static Map* theMap;
};

