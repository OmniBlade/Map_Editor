#pragma once

#include "IList.h"

template <typename T>
class TypeList : public IList
{
public:
	List getList()
	{
		List items;

		unsigned int count = T::Array.count();
		for (unsigned int i = 0; i < count; ++i)
		{
			T* item = T::Array.get(i);
			if (item->valid)
			{
				add(items, item->Name, i, item->ID, true, item->WUIName);
			}
			else
			{
				add(items, item->Name, i, item->ID, false, item->WUIName);
			}
		}

		return items;
	};
};