#include "stdafx.h"
#include "SpecialFlag.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/MapFile/WriterHelper.h"
#include "../../Config.hpp"
#include "../../Log.hpp"

/* static */ SpecialFlag* SpecialFlag::it;
/* static */ SpecialFlag* SpecialFlag::instance()
{
	if (it)
		return it;
	else
		it = new SpecialFlag();
	return it;
}

SpecialFlag::SpecialFlag()
{
}

void SpecialFlag::writeToINI(INIFile& file)
{
	SpecialFlag* it = instance();

	if (!it)
	{
		Log::line("SECTION - SpecialFlags does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	file.SetValue("SpecialFlags", "TiberiumGrows", WriterHelper::getBoolString(it->TiberiumGrows, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "TiberiumSpreads", WriterHelper::getBoolString(it->TiberiumSpreads, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "TiberiumExplosive", WriterHelper::getBoolString(it->TiberiumExplosive, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "DestroyableBridges", WriterHelper::getBoolString(it->DestroyableBridges, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "MCVDeploy", WriterHelper::getBoolString(it->MCVDeploy, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "InitialVeteran", WriterHelper::getBoolString(it->InitialVeteran, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "FixedAlliance", WriterHelper::getBoolString(it->FixedAlliance, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "HarvesterImmune", WriterHelper::getBoolString(it->HarvesterImmune, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "FogOfWar", WriterHelper::getBoolString(it->FogOfWar, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Inert", WriterHelper::getBoolString(it->Inert, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "IonStorms", WriterHelper::getBoolString(it->IonStorms, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Meteorites", WriterHelper::getBoolString(it->Meteorites, WriterHelper::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Visceroids", WriterHelper::getBoolString(it->Visceroids, WriterHelper::BoolType::YESNO));
	if(!it->EscapeMovies) file.SetValue("SpecialFlags", "EscapeMovies", WriterHelper::getBoolString(it->EscapeMovies, WriterHelper::BoolType::YESNO));
}

void SpecialFlag::parse()
{
	INIFile* file = INIManager::instance()->get(Config::mapName);
	INISection* flags = file->getSection("SpecialFlags");

	flags->readBoolValue("TiberiumGrows", TiberiumGrows);
	flags->readBoolValue("TiberiumSpreads", TiberiumSpreads);
	flags->readBoolValue("TiberiumExplosive", TiberiumExplosive);
	flags->readBoolValue("DestroyableBridges", DestroyableBridges);
	flags->readBoolValue("MCVDeploy", MCVDeploy);
	flags->readBoolValue("InitialVeteran", InitialVeteran);
	flags->readBoolValue("FixedAlliance", FixedAlliance);
	flags->readBoolValue("HarvesterImmune", HarvesterImmune);
	flags->readBoolValue("FogOfWar", FogOfWar);
	flags->readBoolValue("Inert", Inert);
	flags->readBoolValue("IonStorms", IonStorms);
	flags->readBoolValue("Meteorites", Meteorites);
	flags->readBoolValue("Visceroids", Visceroids);
	flags->readBoolValue("EscapeMovies", EscapeMovies, true);

		/*
		TiberiumGrows=yes
	TiberiumSpreads=yes
	TiberiumExplosive=no
	DestroyableBridges=yes
	MCVDeploy=no
	InitialVeteran=no
	FixedAlliance=no
	HarvesterImmune=no
	FogOfWar=no
	Inert=no
	IonStorms=no
	Meteorites=no
	Visceroids=no
	EscapeMovies=yes --> default!
		*/

}

