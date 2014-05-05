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

	section->readStringValue("DropPodPuff", DropPodPuff);
	section->readStringValue("VeinAttack", VeinAttack);
	section->readStringValue("Dig", Dig);
	section->readStringValue("AtmosphereEntry", AtmosphereEntry);
	section->readStringValue("TreeFire", TreeFire);
	section->readStringValue("OnFire", OnFire);
	section->readStringValue("Smoke", Smoke);
	section->readStringValue("SmallFire", SmallFire);
	section->readStringValue("LargeFire", LargeFire);


	Animation::Array.findOrAllocate(DropPodPuff);
	Animation::Array.findOrAllocate(VeinAttack);
	Animation::Array.findOrAllocate(Dig);
	Animation::Array.findOrAllocate(AtmosphereEntry);
	allocateList(Animation::Array, TreeFire);
	allocateList(Animation::Array, OnFire);
	Animation::Array.findOrAllocate(Smoke);
	Animation::Array.findOrAllocate(SmallFire);
	Animation::Array.findOrAllocate(LargeFire);
}
