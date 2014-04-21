#include "stdafx.h"
#include "AudioVisual.hpp"
#include "../Types/Animation.hpp"
#include "EntryHelper.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

AudioVisual::AudioVisual()
{
}

void AudioVisual::loadRules(INIFile* file)
{
	INISection* section = file->getSection("AudioVisual");
	if (!section) return;

	Animation::Array.findOrAllocate(section->readStringValue("DropPodPuff"));
	Animation::Array.findOrAllocate(section->readStringValue("VeinAttack"));
	Animation::Array.findOrAllocate(section->readStringValue("Dig"));
	Animation::Array.findOrAllocate(section->readStringValue("AtmosphereEntry"));

	allocateList(Animation::Array, section->readStringValue("TreeFire"));
	allocateList(Animation::Array, section->readStringValue("OnFire"));

	Animation::Array.findOrAllocate(section->readStringValue("Smoke"));
	Animation::Array.findOrAllocate(section->readStringValue("SmallFire"));
	Animation::Array.findOrAllocate(section->readStringValue("LargeFire"));
}
