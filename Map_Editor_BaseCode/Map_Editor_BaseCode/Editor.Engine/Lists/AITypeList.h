#pragma once

#include "IList.h"
#include "../../Config.hpp"

template <typename T>
class AITypeList : public IList
{
public:
	List getList()
	{
		List items;

		unsigned int count = T::Array.count();
		for (unsigned int i = 0; i < count; ++i)
		{
			T* item = T::Array.get(i);
			if (Config::AIReferences)
			{
				add(items, item->Name, i, item->ID);
			}
			else if (item->isGlobal == false)
			{
				add(items, item->Name, i, item->ID);
			}
		}

		return items;
	};
};