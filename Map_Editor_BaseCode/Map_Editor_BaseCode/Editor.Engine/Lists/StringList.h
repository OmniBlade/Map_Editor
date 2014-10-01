#pragma once

#include "IList.h"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"
#include "../../Editor.FileSystem/CsfFile/CSFFile.hpp"

class StringList : public IList
{
public:
	List items;
	
	List getList()
	{
		if (!items.empty())
		{
			return items;
		}

		items.reserve(10000);
		unsigned int count = CSFManager::instance()->files();
		for (unsigned int i = 0; i < count; ++i)
		{
			CSFFile* file = CSFManager::instance()->get(i);
			for (auto& it : file->entryList)
			{
				if (it.second)
					add(items, it.first, -1, it.first, true, it.second.get()->Value);
			}
		}

		return items;
	};
};