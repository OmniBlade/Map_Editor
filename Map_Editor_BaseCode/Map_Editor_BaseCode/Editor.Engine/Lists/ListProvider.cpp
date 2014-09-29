#include "stdafx.h"
#include "ListProvider.h"
#include "TypeList.h"
#include "ObjectList.h"
#include "AITypeList.h"
#include "TrivialList.h"
#include "StringList.h"
#include "NothingList.h"
#include "TechnoList.h"
#include "GroupList.h"
#include "ScriptList.h"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/Animation.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../Editor.Objects.Westwood/Types/ParticleType.hpp"
#include "../../Editor.Objects.Westwood/Types/SuperWeaponType.hpp"
#include "../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../Editor.Objects.Westwood/Types/VoxelAnimType.hpp"
#include "../../Editor.Objects.Westwood/Types/WeaponType.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Movie.h"
#include "../../Editor.Objects.Westwood/AudioVisual/Sound.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Speech.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Theme.hpp"
#include "../Types/House.hpp"
#include "../Types/TeamTypes/ScriptType.hpp"
#include "../Types/TeamTypes/TeamType.hpp"
#include "../Types/TeamTypes/TaskForce.hpp"
#include "../Types/Triggers/Tag.hpp"
#include "../Types/Triggers/Trigger.hpp"
#include "../Types/VariableName.hpp"
#include "../Types/Waypoint.hpp"
#include "../../Log.hpp"

/* static */ std::vector<std::shared_ptr<IList>> ListProvider::typeLists;
/* static */ ListProvider* ListProvider::provider;
/* static */ ListProvider* ListProvider::getProvider()
{
	if (provider)
		return provider;
	else
		provider = new ListProvider();

	return provider;
}

ListProvider::ListProvider()
{
	fillListVector();
}

std::vector<ListItem> ListProvider::getListFor(int param, ScriptType* scr /* = nullptr */)
{
	if (param < 0 || param > (int) typeLists.size())
	{
		Log::line(L"CRIT - Attempt to get a list for ParamType '" + Log::toWString(param) + L"', it does not exist in ListProvider! Returning NothingList.", Log::DEBUG);
		param = 0;
	}
	
	if (scr)
	{
		ScriptList list;
		return list.getList(scr); //38 = only one that takes ScriptType
	}
	else if (param == 38 && !scr)
	{
		//Param 38 is ScriptType action line list, requires ScriptType pointer
		//Can't return something that isn't there, throw error and return nothing
		Log::line(L"WARN - Attempt to get a list for a ScriptType which doesn't exist! Returning NothingList.", Log::DEBUG);
		return getListFor(0);
	}
	else
	{
		return typeLists[param]->getList();
	}
}

std::vector<ListItem> ListProvider::getCombinedList(std::vector<int> params)
{
	std::vector<ListItem> lists;

	for (unsigned int i = 0; i < params.size(); ++i)
	{
		std::vector<ListItem> tempList = typeLists[params[i]].get()->getList();
		lists.insert(lists.end(), tempList.begin(), tempList.end());

		if (params[i] == 38)
		{
			/*
				"Why?", I hear you say, "Why not?"
				Simply because this list requires a ScriptType pointer, and you don't pass that on when calling for a combined list
				(hence the parameters)
			*/
			Log::line(L"SEVERE! - Attempt to combine a list for ScriptType lines, it simple doesn't work like that!", Log::DEBUG);
		}
	}

	return lists;
}

/*
	WARNING!
	DO NOT EVER, I REPEAT: DO NOT EVER CHANGE THE ORDER OF THIS FUNCTION!
	Contact RP if something is up, this list is entirely hardcoded!
	It is directly tied to the PARAMS file, note that the order of that file and below are identical, it's for a reason!
*/
void ListProvider::fillListVector()
{
	typeLists.emplace_back(std::make_shared<NothingList>()); // NOTHING
	typeLists.emplace_back(std::make_shared<TypeList<AircraftType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Animation>>());
	typeLists.emplace_back(std::make_shared<TypeList<BuildingType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Speech>>());
	typeLists.emplace_back(std::make_shared<ObjectList<House>>());
	typeLists.emplace_back(std::make_shared<TypeList<InfantryType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Movie>>());
	typeLists.emplace_back(std::make_shared<TypeList<ParticleType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Sound>>());
	typeLists.emplace_back(std::make_shared<StringList>());
	typeLists.emplace_back(std::make_shared<TypeList<SuperWeaponType>>());
	typeLists.emplace_back(std::make_shared<ObjectList<Tag>>());
	typeLists.emplace_back(std::make_shared<AITypeList<TeamType>>());
	typeLists.emplace_back(std::make_shared<TechnoList>());
	typeLists.emplace_back(std::make_shared<TypeList<Theme>>());
	typeLists.emplace_back(std::make_shared<ObjectList<Trigger>>());
	typeLists.emplace_back(std::make_shared<ObjectList<VehicleType>>());
	typeLists.emplace_back(std::make_shared<ObjectList<VariableName>>());
	typeLists.emplace_back(std::make_shared<ObjectList<GlobalVariableName>>());
	typeLists.emplace_back(std::make_shared<ObjectList<Waypoint>>());
	typeLists.emplace_back(std::make_shared<TypeList<WeaponType>>());
	typeLists.emplace_back(std::make_shared<BoolList>());
	typeLists.emplace_back(std::make_shared<QuarryList>());
	typeLists.emplace_back(std::make_shared<GroupList>());
	typeLists.emplace_back(std::make_shared<SpeedList>());
	typeLists.emplace_back(std::make_shared<TypeList<VoxelAnimType>>());
	typeLists.emplace_back(std::make_shared<CrateList>());
	typeLists.emplace_back(std::make_shared<SBubbleList>());
	typeLists.emplace_back(std::make_shared<LBehaviorList>());
	typeLists.emplace_back(std::make_shared<REventList>());
	typeLists.emplace_back(std::make_shared<ShowerList>());
	typeLists.emplace_back(std::make_shared<TabList>());
	typeLists.emplace_back(std::make_shared<ZoomList>());
	typeLists.emplace_back(std::make_shared<MissionList>());
	typeLists.emplace_back(std::make_shared<FacingList>());
	typeLists.emplace_back(std::make_shared<AITypeList<ScriptType>>());
	typeLists.emplace_back(std::make_shared<SplitList>());
	typeLists.emplace_back(std::make_shared<ScriptList>());
	typeLists.emplace_back(std::make_shared<TechLevelList>());
	typeLists.emplace_back(std::make_shared<AITypeList<TaskForce>>());
	typeLists.emplace_back(std::make_shared<TypeList<Country>>());		// This will probably never used, maybe in MP?
	typeLists.emplace_back(std::make_shared<MPHouseList>());
}