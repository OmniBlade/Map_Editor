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

	if (isSP()) file.SetValue("Basic", "EndOfGame", BoolWriter::getBoolString(it->EndOfGame, BoolWriter::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "SkipScore", BoolWriter::getBoolString(it->SkipScore, BoolWriter::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "OneTimeOnly", BoolWriter::getBoolString(it->OneTimeOnly, BoolWriter::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "SkipMapSelect", BoolWriter::getBoolString(it->SkipMapSelect, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "Official", BoolWriter::getBoolString(it->Official, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "IgnoreGlobalAITriggers", BoolWriter::getBoolString(it->IgnoreGlobalAITriggers, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "TruckCrate", BoolWriter::getBoolString(it->TruckCrate, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "TrainCrate", BoolWriter::getBoolString(it->TrainCrate, BoolWriter::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "CivEvac", BoolWriter::getBoolString(it->CivEvac, BoolWriter::BoolType::YESNO));
	if (isSP()) file.SetValue("Basic", "TimerInherit", BoolWriter::getBoolString(it->TimerInherit, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "FillSilos", BoolWriter::getBoolString(it->FillSilos, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "MultiplayerOnly", BoolWriter::getBoolString(it->MultiplayerOnly, BoolWriter::BoolType::BIT));
	file.SetValue("Basic", "TiberiumGrowthEnabled", BoolWriter::getBoolString(it->TiberiumGrowthEnabled, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "VeinGrowthEnabled", BoolWriter::getBoolString(it->VeinGrowthEnabled, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "IceGrowthEnabled", BoolWriter::getBoolString(it->IceGrowthEnabled, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "TiberiumDeathToVisceroid", BoolWriter::getBoolString(it->TibDeathToVisc, BoolWriter::BoolType::YESNO));
	file.SetValue("Basic", "FreeRadar", BoolWriter::getBoolString(it->FreeRadar, BoolWriter::BoolType::YESNO));
}

void Basic::parse()
{
	INIFile* map = INIManager::instance()->get(Config::mapName);
	INISection* basic = map->getSection("Basic");

	basic->readDeletableStringValue("Name", Name, "No name");
	basic->readDeletableStringValue("Player", Player);
	basic->readDeletableStringValue("Briefing", Briefing, "<none>");
	basic->readDeletableStringValue("Theme", ThemeStr, "<none>");
	basic->readDeletableStringValue("Intro", Intro, "<none>");
	basic->readDeletableStringValue("Brief", Brief, "<none>");
	basic->readDeletableStringValue("Win", Win, "<none>");
	basic->readDeletableStringValue("Lose", Lose, "<none>");
	basic->readDeletableStringValue("Action", Action, "<none>");
	basic->readDeletableStringValue("PostScore", PostScore, "<none>");
	basic->readDeletableStringValue("PreMapSelect", PreMapSelect, "<none>");
	basic->readDeletableStringValue("NextScenario", NextScenario, "<none>");
	basic->readDeletableStringValue("AltNextScenario", AltNextScenario, "<none>");
	basic->readDeletableStringValue("GameMode", GameModesStr);
	basic->readDeletableStringValue("AllowableUnits", AllowableUnitsStr);
	basic->readDeletableStringValue("AllowableUnitsMaximums", AllowableMaxStr);
	
	basic->readDeletableFloatValue("CarryOverMoney", CarryOverMoney);
	basic->readDeletableIntValue("NewINIFormat", NewINIFormat, 4);
	basic->readDeletableIntValue("CarryOverCap", CarryOverCap, -1);
	basic->readDeletableIntValue("Percent", Percent, -1);
	basic->readDeletableIntValue("StartingDropships", StartingDropShips, -1);
	basic->readDeletableIntValue("HomeCell", HomeCell, -1);
	basic->readDeletableIntValue("AltHomeCell", AltHomeCell, -1);
	basic->readDeletableIntValue("InitTime", InitTime, -1);
	basic->readDeletableIntValue("MaxPlayer", MaxPlayer, -1);
	basic->readDeletableIntValue("MinPlayer", MinPlayer, -1);

	basic->readDeletableBoolValue("EndOfGame", EndOfGame);
	basic->readDeletableBoolValue("SkipScore", SkipScore);
	basic->readDeletableBoolValue("OneTimeOnly", OneTimeOnly);
	basic->readDeletableBoolValue("SkipMapSelect", SkipMapSelect);
	basic->readDeletableBoolValue("Official", Official);
	basic->readDeletableBoolValue("IgnoreGlobalAITriggers", IgnoreGlobalAITriggers);
	basic->readDeletableBoolValue("TruckCrate", TruckCrate);
	basic->readDeletableBoolValue("TrainCrate", TrainCrate);
	basic->readDeletableBoolValue("CivEvac", CivEvac);
	basic->readDeletableBoolValue("TimerInherit", TimerInherit);
	basic->readDeletableBoolValue("FillSilos", FillSilos);
	basic->readDeletableBoolValue("MultiplayerOnly", MultiplayerOnly);
	basic->readDeletableBoolValue("TiberiumGrowthEnabled", TiberiumGrowthEnabled);
	basic->readDeletableBoolValue("VeinGrowthEnabled", VeinGrowthEnabled);
	basic->readDeletableBoolValue("IceGrowthEnabled", IceGrowthEnabled);
	basic->readDeletableBoolValue("TiberiumDeathToVisceroid", TibDeathToVisc);
	basic->readDeletableBoolValue("FreeRadar", FreeRadar);

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

	if (!basic->size())
	{
		map->deleteSection("Basic");
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