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

	file.SetValue("SpecialFlags", "TiberiumGrows", BoolWriter::getBoolString(it->TiberiumGrows, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "TiberiumSpreads", BoolWriter::getBoolString(it->TiberiumSpreads, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "TiberiumExplosive", BoolWriter::getBoolString(it->TiberiumExplosive, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "DestroyableBridges", BoolWriter::getBoolString(it->DestroyableBridges, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "MCVDeploy", BoolWriter::getBoolString(it->MCVDeploy, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "InitialVeteran", BoolWriter::getBoolString(it->InitialVeteran, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "FixedAlliance", BoolWriter::getBoolString(it->FixedAlliance, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "HarvesterImmune", BoolWriter::getBoolString(it->HarvesterImmune, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "FogOfWar", BoolWriter::getBoolString(it->FogOfWar, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Inert", BoolWriter::getBoolString(it->Inert, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "IonStorms", BoolWriter::getBoolString(it->IonStorms, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Meteorites", BoolWriter::getBoolString(it->Meteorites, BoolWriter::BoolType::YESNO));
	file.SetValue("SpecialFlags", "Visceroids", BoolWriter::getBoolString(it->Visceroids, BoolWriter::BoolType::YESNO));
	if(!it->EscapeMovies) file.SetValue("SpecialFlags", "EscapeMovies", BoolWriter::getBoolString(it->EscapeMovies, BoolWriter::BoolType::YESNO));
}

void SpecialFlag::parse(INIFile* map)
{
	INISection* flags = map->getSection("SpecialFlags");

	flags->readDeletableBoolValue("TiberiumGrows", TiberiumGrows);
	flags->readDeletableBoolValue("TiberiumSpreads", TiberiumSpreads);
	flags->readDeletableBoolValue("TiberiumExplosive", TiberiumExplosive);
	flags->readDeletableBoolValue("DestroyableBridges", DestroyableBridges);
	flags->readDeletableBoolValue("MCVDeploy", MCVDeploy);
	flags->readDeletableBoolValue("InitialVeteran", InitialVeteran);
	flags->readDeletableBoolValue("FixedAlliance", FixedAlliance);
	flags->readDeletableBoolValue("HarvesterImmune", HarvesterImmune);
	flags->readDeletableBoolValue("FogOfWar", FogOfWar);
	flags->readDeletableBoolValue("Inert", Inert);
	flags->readDeletableBoolValue("IonStorms", IonStorms);
	flags->readDeletableBoolValue("Meteorites", Meteorites);
	flags->readDeletableBoolValue("Visceroids", Visceroids);
	flags->readDeletableBoolValue("EscapeMovies", EscapeMovies, true);

	if (!flags->size())
	{
		map->deleteSection("SpecialFlags");
	}

}

