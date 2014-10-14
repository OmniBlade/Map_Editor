#include "stdafx.h"
#include "Basic.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/MapFile/WriterHelper.h"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include "../Types/House.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Movie.h"
#include "../../Editor.Objects.Westwood/AudioVisual/Theme.hpp"

/* static */ Basic* Basic::instance;
/* static */ Basic* Basic::getBasic()
{
	if (instance)
		return instance;
	else
		instance = new Basic();
	return instance;
}

Basic::Basic()
{
}

bool Basic::isMP()
{
	return getBasic()->pPlayer ? false : true;
}

bool Basic::isSP()
{
	return getBasic()->pPlayer ? true : false;
}

bool Basic::isCoop()
{
	return getBasic()->isACoop && isMP();
}

void Basic::writeToINI(INIFile& file)
{
	Basic* it = getBasic();

	if (!it)
	{
		Log::line("SECTION - Basic does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	file.SetValue("Basic", "Name", it->Name);
	if (isSP()) file.SetValue("Basic", "Player", it->Player);
	if (it->Briefing != "<none>" && isSP()) file.SetValue("Basic", "Briefing", it->Briefing);
	if (it->ThemeStr != "<none>") file.SetValue("Basic", "Theme", it->ThemeStr);
	if (it->Intro != "<none>" && isSP()) file.SetValue("Basic", "Intro", it->Intro);
	if (it->Brief != "<none>" && isSP()) file.SetValue("Basic", "Brief", it->Brief);
	if (it->Win != "<none>" && isSP()) file.SetValue("Basic", "Win", it->Win);
	if (it->Lose != "<none>" && isSP()) file.SetValue("Basic", "Lose", it->Lose);
	if (it->Action != "<none>" && isSP()) file.SetValue("Basic", "Action", it->Action);
	if (it->PostScore != "<none>" && isSP()) file.SetValue("Basic", "PostScore", it->PostScore);
	if (it->PreMapSelect != "<none>" && isSP()) file.SetValue("Basic", "PreMapSelect", it->PreMapSelect);
	if (it->NextScenario != "<none>" && isSP()) file.SetValue("Basic", "NextScenario", it->NextScenario);
	if (it->AltNextScenario != "<none>" && isSP()) file.SetValue("Basic", "AltNextScenario", it->AltNextScenario);
	
	if (it->GameModes.size() > 0 && isMP()) file.SetValue("Basic", "GameMode", it->gamemodesAsString());
	if (it->AllowableUnits.size() > 0 && isSP()) file.SetValue("Basic", "AllowableUnits", it->unitsAsString()); //TS?
	if (it->AllowableUnitsMaximums.size() > 0 && isSP()) file.SetValue("Basic", "AllowableUnitsMaximums", it->unitsMaxAsString()); // TS?
	
	if (isSP()) file.SetValue("Basic", "CarryOverMoney", Log::toString(it->CarryOverMoney));
	if (isSP()) file.SetValue("Basic", "NewINIFormat", Log::toString(it->NewINIFormat));
	if (isSP()) file.SetValue("Basic", "Percent", Log::toString(it->Percent));
	if (isSP() && it->StartingDropShips > 0) file.SetValue("Basic", "StartingDropShips", Log::toString(it->StartingDropShips)); //TS?
	if (isSP()) file.SetValue("Basic", "HomeCell", Log::toString(it->HomeCell));
	if (isSP()) file.SetValue("Basic", "AltHomeCell", Log::toString(it->AltHomeCell));
	if (isSP()) file.SetValue("Basic", "InitTime", Log::toString(it->InitTime));
	if (isMP()) file.SetValue("Basic", "MaxPlayer", Log::toString(it->MaxPlayer));
	if (isMP()) file.SetValue("Basic", "MinPlayer", Log::toString(it->MinPlayer));

	if (isSP()) file.SetValue("Basic", "EndOfGame", WriterHelper::getBoolString(it->EndOfGame, WriterHelper::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "SkipScore", WriterHelper::getBoolString(it->SkipScore, WriterHelper::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "OneTimeOnly", WriterHelper::getBoolString(it->OneTimeOnly, WriterHelper::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "SkipMapSelect", WriterHelper::getBoolString(it->SkipMapSelect, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "Official", WriterHelper::getBoolString(it->Official, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "IgnoreGlobalAITriggers", WriterHelper::getBoolString(it->IgnoreGlobalAITriggers, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "TruckCrate", WriterHelper::getBoolString(it->TruckCrate, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "TrainCrate", WriterHelper::getBoolString(it->TrainCrate, WriterHelper::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "CivEvac", WriterHelper::getBoolString(it->CivEvac, WriterHelper::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "TimerInherit", WriterHelper::getBoolString(it->TimerInherit, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "FillSilos", WriterHelper::getBoolString(it->FillSilos, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "MultiplayerOnly", WriterHelper::getBoolString(it->MultiplayerOnly, WriterHelper::BoolType::BIT));
	file.SetValue("Basic", "TiberiumGrowthEnabled", WriterHelper::getBoolString(it->TiberiumGrowthEnabled, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "VeinGrowthEnabled", WriterHelper::getBoolString(it->VeinGrowthEnabled, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "IceGrowthEnabled", WriterHelper::getBoolString(it->IceGrowthEnabled, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "TiberiumDeathToVisceroid", WriterHelper::getBoolString(it->TibDeathToVisc, WriterHelper::BoolType::YESNO));
	file.SetValue("Basic", "FreeRadar", WriterHelper::getBoolString(it->FreeRadar, WriterHelper::BoolType::YESNO));
}

void Basic::parse()
{
	INIFile* map = INIManager::instance()->get(Config::mapName);
	INISection* basic = map->getSection("Basic");

	basic->readStringValue("Name", Name, "No name");
	basic->readStringValue("Player", Player);
	basic->readStringValue("Briefing", Briefing, "<none>");
	basic->readStringValue("Theme", ThemeStr, "<none>");
	basic->readStringValue("Intro", Intro, "<none>");
	basic->readStringValue("Brief", Brief, "<none>");
	basic->readStringValue("Win", Win, "<none>");
	basic->readStringValue("Lose", Lose, "<none>");
	basic->readStringValue("Action", Action, "<none>");
	basic->readStringValue("PostScore", PostScore, "<none>");
	basic->readStringValue("PreMapSelect", PreMapSelect, "<none>");
	basic->readStringValue("NextScenario", NextScenario, "<none>");
	basic->readStringValue("AltNextScenario", AltNextScenario, "<none>");
	basic->readStringValue("GameMode", GameModesStr);
	basic->readStringValue("AllowableUnits", AllowableUnitsStr);
	basic->readStringValue("AllowableUnitsMaximums", AllowableMaxStr);
	
	basic->readFloatValue("CarryOverMoney", CarryOverMoney);
	basic->readIntValue("NewINIFormat", NewINIFormat, 4);
	basic->readIntValue("CarryOverCap", CarryOverCap, -1);
	basic->readIntValue("Percent", Percent, -1);
	basic->readIntValue("StartingDropShips", StartingDropShips, -1);
	basic->readIntValue("HomeCell", HomeCell, -1);
	basic->readIntValue("AltHomeCell", AltHomeCell, -1);
	basic->readIntValue("InitTime", InitTime, -1);
	basic->readIntValue("MaxPlayer", MaxPlayer, -1);
	basic->readIntValue("MinPlayer", MinPlayer, -1);

	basic->readBoolValue("EndOfGame", EndOfGame);
	basic->readBoolValue("SkipScore", SkipScore);
	basic->readBoolValue("OneTimeOnly", OneTimeOnly);
	basic->readBoolValue("SkipMapSelect", SkipMapSelect);
	basic->readBoolValue("Official", Official);
	basic->readBoolValue("IgnoreGlobalAITriggers", IgnoreGlobalAITriggers);
	basic->readBoolValue("TruckCrate", TruckCrate);
	basic->readBoolValue("TrainCrate", TrainCrate);
	basic->readBoolValue("CivEvac", CivEvac);
	basic->readBoolValue("TimerInherit", TimerInherit);
	basic->readBoolValue("FillSilos", FillSilos);
	basic->readBoolValue("MultiplayerOnly", MultiplayerOnly);
	basic->readBoolValue("TiberiumGrowthEnabled", TiberiumGrowthEnabled);
	basic->readBoolValue("VeinGrowthEnabled", VeinGrowthEnabled);
	basic->readBoolValue("IceGrowthEnabled", IceGrowthEnabled);
	basic->readBoolValue("TiberiumDeathToVisceroid", TibDeathToVisc);
	basic->readBoolValue("FreeRadar", FreeRadar);

	LineSplitter gmsplit(GameModesStr);
	for (unsigned int i = 0; i < gmsplit.size(); ++i)
	{
		GameModes.push_back(gmsplit.peekFromIndex_string(i));
		if (GameModes.back() == "cooperative") //Err... hardcoding?
		{
			isACoop = true;
		}
	}

	LineSplitter ausplit(AllowableUnitsStr);
	for (unsigned int i = 0; i < ausplit.size(); ++i)
	{
		AllowableUnits.push_back(ausplit.peekFromIndex_string(i));
	}

	LineSplitter aumSplit(AllowableMaxStr);
	for (unsigned int i = 0; i < aumSplit.size(); ++i)
	{
		AllowableUnitsMaximums.push_back(aumSplit.peekFromIndex_int(i));
	}
}

void Basic::assignPointers()
{
	pPlayer = House::Array.find(Player);
	pTheme = Theme::Array.find(ThemeStr);
	pBriefing = Movie::Array.find(Briefing);
	pIntro = Movie::Array.find(Intro);
	pBrief = Movie::Array.find(Brief);
	pWin = Movie::Array.find(Win);
	pLose = Movie::Array.find(Lose);
	pAction = Movie::Array.find(Action);
	pPostScore = Movie::Array.find(PostScore);
}

std::string Basic::gamemodesAsString()
{
	std::string ret;

	for (auto& it : GameModes)
	{
		ret.append("," + it);
	}

	return ret.substr(1, ret.size());
}

std::string Basic::unitsAsString()
{
	std::string ret;

	for (auto& it : AllowableUnits)
	{
		ret.append("," + it);
	}

	return ret.substr(1, ret.size());
}

std::string Basic::unitsMaxAsString()
{
	std::string ret;

	for (auto& it : AllowableUnitsMaximums)
	{
		ret.append("," + Log::toString(it));
	}

	return ret.substr(1, ret.size());
}