#include "stdafx.h"
#include "GameMode.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"

GameMode::GameMode(const std::string& line)
{
	parse(line);
}

void GameMode::parse(const std::string& line)
{
	LineSplitter split(line);

	if (split.pop(GUIName) && split.pop(STTName) && split.pop(fileName) && split.pop(iniName) && split.pop(rmgAllowed))
	{
		if (!GUIName.empty())
		{
			WGUIName = CSFManager::getManager()->getValue(GUIName);
		}

		if (!STTName.empty())
		{
			WSTTName = CSFManager::getManager()->getValue(STTName);
		}
	}
	else
	{
		Log::note("Unable to parse GameMode file with line '" + line + "'", Log::DEBUG);
	}
}