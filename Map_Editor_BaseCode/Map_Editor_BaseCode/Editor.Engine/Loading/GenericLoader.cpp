#include "stdafx.h"
#include "GenericLoader.h"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Movie.h"
#include "../../Editor.Objects.Westwood/AudioVisual/Theme.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Sound.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Speech.hpp"
#include "../../Config.hpp"
#include "MapLoaderHelpers.hpp"

GenericLoader::GenericLoader()
{
}


GenericLoader::~GenericLoader()
{
}

void GenericLoader::loadAudioVisual()
{
	INIFile* speech = INIManager::instance()->get(Config::eva);
	INIFile* sound = INIManager::instance()->get(Config::sound);
	INIFile* theme = INIManager::instance()->get(Config::theme);
	INIFile* art = INIManager::instance()->get(Config::art);

	allocateAll(Speech::Array, speech, "DialogList");
	allocateAll(Sound::Array, sound, "SoundList");
	allocateAll(Theme::Array, theme, "Themes");
	loadFromSingleINI(Speech::Array, *speech);
	loadFromSingleINI(Sound::Array, *sound);
	loadFromSingleINI(Theme::Array, *theme);

	INISection* movielist = art->getSection("Movies");

	for (const auto& it : *movielist)
	{
		Movie::Array.make();
		Movie::Array.typeList[Movie::Array.count() - 1].get()->parse(it, movielist->getValue(it.c_str()));
	}
}

void GenericLoader::reloadAudioVisual()
{
	Speech::Array.clear();
	Sound::Array.clear();
	Theme::Array.clear();
	Movie::Array.clear();

	loadAudioVisual();
}