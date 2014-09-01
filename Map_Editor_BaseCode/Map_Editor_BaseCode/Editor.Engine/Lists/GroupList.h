#pragma once

#include "IList.h"
#include <memory>
#include <set>
#include "../Types/Objects/Aircraft.hpp"
#include "../Types/Objects/Infantry.hpp"
#include "../Types/Objects/Unit.hpp"

class GroupList : public IList
{
public:
	List getList()
	{
		List items;
		std::set<int> groups;

		unsigned int countAT = Aircraft::Array.count();
		for (unsigned int i = 0; i < countAT; ++i)
		{
			Aircraft* item = Aircraft::Array.get(i);
			if (!exists(groups, item->group))
				groups.insert(item->group);
		}

		unsigned int countIT = Infantry::Array.count();
		for (unsigned int i = 0; i < countIT; ++i)
		{
			Infantry* item = Infantry::Array.get(i);
			if (!exists(groups, item->group))
				groups.insert(item->group);
		}

		unsigned int countUT = Unit::Array.count();
		for (unsigned int i = 0; i < countUT; ++i)
		{
			Unit* item = Unit::Array.get(i);
			if (!exists(groups, item->group))
				groups.insert(item->group);
		}

		for (auto& aGroup : groups)
		{
			add(items, Log::toString(aGroup), aGroup);
		}

		return items;
	};

	/*
		We don't want any duplicate group ID numbers in the list!
	*/
	bool exists(std::set<int>& items, int groupID)
	{
		if (std::find(items.begin(), items.end(), groupID) == items.end())
		{
			return false;
		}
		return true;
	}
};