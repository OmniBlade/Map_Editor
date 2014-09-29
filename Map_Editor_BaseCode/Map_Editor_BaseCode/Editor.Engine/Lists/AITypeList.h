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
			if (item->isGlobal == true)
			{
				add(items, item->Name, i, item->ID, false);
			}
			else
			{
				add(items, item->Name, i, item->ID, true);
			}
		}

		return items;
	};
};