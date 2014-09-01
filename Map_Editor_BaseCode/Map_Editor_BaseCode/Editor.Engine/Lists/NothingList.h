#pragma once

#include "IList.h"

class NothingList : public IList
{
	List getList()
	{
		List items;
		return items;
	};
};