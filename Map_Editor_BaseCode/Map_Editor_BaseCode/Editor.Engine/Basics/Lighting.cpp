#include "stdafx.h"
#include "Lighting.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../GameDefinition.h"
#include "../../Config.hpp"
#include "../../Log.hpp"

/* static */ Lighting* Lighting::it;
/* static */ Lighting* Lighting::instance()
{
	if (it)
		return it;
	else
		it = new Lighting();
	return it;
}

Lighting::Lighting()
{
}

void Lighting::writeToINI(INIFile& file)
{
	Lighting* it = instance();

	if (!it)
	{
		Log::line("SECTION - Lighting does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	file.SetValue("Lighting", "Ambient", Log::toString(it->Ambient));
	file.SetValue("Lighting", "Red", Log::toString(it->Red));
	file.SetValue("Lighting", "Green", Log::toString(it->Green));
	file.SetValue("Lighting", "Blue", Log::toString(it->Blue));
	file.SetValue("Lighting", "Ground", Log::toString(it->Ground));
	file.SetValue("Lighting", "Level", Log::toString(it->Level));
	file.SetValue("Lighting", "IonAmbient", Log::toString(it->IonAmbient));
	file.SetValue("Lighting", "IonRed", Log::toString(it->IonRed));
	file.SetValue("Lighting", "IonGreen", Log::toString(it->IonGreen));
	file.SetValue("Lighting", "IonBlue", Log::toString(it->IonBlue));
	file.SetValue("Lighting", "IonGround", Log::toString(it->IonGround));
	file.SetValue("Lighting", "IonLevel", Log::toString(it->IonLevel));

	if (Game::title == Game::Type::Expansion)
	{
		file.SetValue("Lighting", "DominatorAmbient", Log::toString(it->DomAmbient));
		file.SetValue("Lighting", "DominatorRed", Log::toString(it->DomRed));
		file.SetValue("Lighting", "DominatorGreen", Log::toString(it->DomGreen));
		file.SetValue("Lighting", "DominatorBlue", Log::toString(it->DomBlue));
		file.SetValue("Lighting", "DominatorGround", Log::toString(it->DomGround));
		file.SetValue("Lighting", "DominatorLevel", Log::toString(it->DomLevel));
		file.SetValue("Lighting", "DominatorAmbientChangeRate", Log::toString(it->DomChangeRate));
	}

	if(it->NukeChangeRate > 0.0f) file.SetValue("Lighting", "NukeAmbientChangeRate", Log::toString(it->NukeChangeRate));
}

void Lighting::parse(INIFile* map)
{
	INISection* lighting = map->getSection("Lighting");

	lighting->readDeletableFloatValue("Ambient", Ambient);
	lighting->readDeletableFloatValue("Red", Red);
	lighting->readDeletableFloatValue("Green", Green);
	lighting->readDeletableFloatValue("Blue", Blue);
	lighting->readDeletableFloatValue("Ground", Ground);
	lighting->readDeletableFloatValue("Level", Level);
	lighting->readDeletableFloatValue("IonAmbient", IonAmbient);
	lighting->readDeletableFloatValue("IonRed", IonRed);
	lighting->readDeletableFloatValue("IonGreen", IonGreen);
	lighting->readDeletableFloatValue("IonBlue", IonBlue);
	lighting->readDeletableFloatValue("IonGround", IonGround);
	lighting->readDeletableFloatValue("IonLevel", IonLevel);
	lighting->readDeletableFloatValue("NukeAmbientChangeRate", NukeChangeRate, 0.0f);

	if (Game::title == Game::Type::Expansion)
	{
		lighting->readDeletableFloatValue("DominatorAmbient", DomAmbient);
		lighting->readDeletableFloatValue("DominatorRed", DomRed);
		lighting->readDeletableFloatValue("DominatorGreen", DomGreen);
		lighting->readDeletableFloatValue("DominatorBlue", DomBlue);
		lighting->readDeletableFloatValue("DominatorGround", DomGround);
		lighting->readDeletableFloatValue("DominatorLevel", DomLevel);
		lighting->readDeletableFloatValue("DominatorAmbientChangeRate", DomChangeRate);
	}

	if (!lighting->size())
	{
		map->deleteSection("Lighting");
	}
}