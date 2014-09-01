#pragma once

#include "IList.h"

template <typename T>
class ObjectList : public IList
{
public:
	List getList()
	{
		List items;

		unsigned int count = T::Array.count();
		for (unsigned int i = 0; i < count; ++i)
		{
			T* item = T::Array.get(i);
			add(items, item->Name, i, item->ID);
		}

		return items;
	};
};