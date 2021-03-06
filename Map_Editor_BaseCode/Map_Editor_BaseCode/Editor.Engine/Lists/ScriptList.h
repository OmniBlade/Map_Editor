#pragma once

#include "IList.h"
#include "../Types/TeamTypes/ScriptType.hpp"
#include "../Types/TeamTypes/ScriptAction.hpp"
#include "../../Editor.FileSystem/MapFile/Triggers/SActionType.hpp"

class ScriptList : public IList
{
public:
	List getList()
	{
		List items;
		return items;
	}

	List getList(ScriptType* pScript)
	{
		List items;	
		
		for (unsigned int i = 0; i < pScript->actionList.size(); ++i)
		{
			add(items, pScript->actionList[i]->pActionType->getNameWithParams(), i+1);
		}

		return items;
	};
};