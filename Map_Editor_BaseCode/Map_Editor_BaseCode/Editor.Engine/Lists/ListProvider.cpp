#include "stdafx.h"
#include "ListProvider.h"
#include "TypeList.h"
#include "ObjectList.h"
#include "TrivialList.h"
#include "NothingList.h"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/Animation.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
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

ListProvider::ListProvider()
{
	fillListVector();
}

std::vector<ListItem> ListProvider::getListFor(int param)
{
	if (param < 0 || param > typeLists.size())
	{
		Log::line(L"CRITICAL! - Attempt to get a list for ParamType '" + Log::toWString(param) + L"', it does not exist in ListProvider! Returning NothingList.", Log::DEBUG);
		param = 0;
	}
	return typeLists[param].get()->getList();
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
	typeLists.emplace_back(std::make_shared<NothingList>());
//	/* TODO */ typeLists.emplace_back(std::make_shared<NothingList>()); // TODO: remove it!
	typeLists.emplace_back(std::make_shared<TypeList<Speech>>());
	typeLists.emplace_back(std::make_shared<ObjectList<House>>());
	typeLists.emplace_back(std::make_shared<TypeList<InfantryType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Movie>>());
	typeLists.emplace_back(std::make_shared<TypeList<ParticleType>>());
	typeLists.emplace_back(std::make_shared<TypeList<Sound>>()); //10
	/* TODO */ typeLists.emplace_back(std::make_shared<NothingList>());	// TODO: INVENT SOMETHING /*CSF STRINGS*/
	typeLists.emplace_back(std::make_shared<TypeList<SuperWeaponType>>());
	typeLists.emplace_back(std::make_shared<ObjectList<Tag>>());
	typeLists.emplace_back(std::make_shared<ObjectList<TeamType>>());
	/* TODO */ typeLists.emplace_back(std::make_shared<NothingList>()); // TODO: INVENT SOMETHING
	typeLists.emplace_back(std::make_shared<TypeList<Theme>>());
	typeLists.emplace_back(std::make_shared<ObjectList<Trigger>>());
	typeLists.emplace_back(std::make_shared<ObjectList<VehicleType>>());
	typeLists.emplace_back(std::make_shared<ObjectList<VariableName>>());
	typeLists.emplace_back(std::make_shared<ObjectList<GlobalVariableName>>()); //20
	typeLists.emplace_back(std::make_shared<ObjectList<Waypoint>>());
	typeLists.emplace_back(std::make_shared<TypeList<WeaponType>>());
	typeLists.emplace_back(std::make_shared<BoolList>());
	typeLists.emplace_back(std::make_shared<NothingList>()); // LEFT
	typeLists.emplace_back(std::make_shared<NothingList>()); // TOP
	typeLists.emplace_back(std::make_shared<NothingList>()); // WIDTH
	typeLists.emplace_back(std::make_shared<NothingList>()); // HEIGHT
	typeLists.emplace_back(std::make_shared<QuarryList>());
	typeLists.emplace_back(std::make_shared<NothingList>()); // SECONDS 
	typeLists.emplace_back(std::make_shared<NothingList>()); // CREDITS //30
	typeLists.emplace_back(std::make_shared<NothingList>()); // GROUP
	typeLists.emplace_back(std::make_shared<SpeedList>());
	typeLists.emplace_back(std::make_shared<TypeList<VoxelAnimType>>());
	typeLists.emplace_back(std::make_shared<CrateList>());
	typeLists.emplace_back(std::make_shared<SBubbleList>());
	typeLists.emplace_back(std::make_shared<LBehaviorList>());
	typeLists.emplace_back(std::make_shared<REventList>());
	typeLists.emplace_back(std::make_shared<ShowerList>());
	typeLists.emplace_back(std::make_shared<NothingList>()); // NUMBER
	typeLists.emplace_back(std::make_shared<NothingList>()); // FRAMES // 40
	typeLists.emplace_back(std::make_shared<TabList>());
	typeLists.emplace_back(std::make_shared<NothingList>()); // PERCENTAGE
	typeLists.emplace_back(std::make_shared<ZoomList>());
	typeLists.emplace_back(std::make_shared<NothingList>()); // AMOUNT
	typeLists.emplace_back(std::make_shared<NothingList>()); // AMBIENT RATE
	typeLists.emplace_back(std::make_shared<NothingList>()); // RETINT VALUE
	typeLists.emplace_back(std::make_shared<NothingList>()); // LIGHTING LEVEL
	typeLists.emplace_back(std::make_shared<NothingList>()); // AMBIENT STEP
	typeLists.emplace_back(std::make_shared<NothingList>()); // AMBIENT LEVEL
	typeLists.emplace_back(std::make_shared<MissionList>()); // 50
	typeLists.emplace_back(std::make_shared<FacingList>());
	typeLists.emplace_back(std::make_shared<ObjectList<ScriptType>>());
	typeLists.emplace_back(std::make_shared<SplitList>());
	/* TODO	*/typeLists.emplace_back(std::make_shared<NothingList>());	// SCRIPT LINE: TODO IMPLEMENT
	typeLists.emplace_back(std::make_shared<NothingList>()); // CELL
	typeLists.emplace_back(std::make_shared<TechLevelList>());
	typeLists.emplace_back(std::make_shared<ObjectList<TaskForce>>());
}