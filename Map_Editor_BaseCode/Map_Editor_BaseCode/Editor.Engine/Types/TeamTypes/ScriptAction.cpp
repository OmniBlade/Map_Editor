#include "stdafx.h"
#include "ScriptAction.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

ScriptAction::ScriptAction(const std::string& list)
{
	LineSplitter split(list);
	split.pop(action);
	split.pop(parameter);
}
