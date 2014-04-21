#include "stdafx.h"
#include "WarheadType.hpp"
#include "../General/EntryHelper.hpp"
#include "Animation.hpp"
#include "VoxelAnimType.hpp"

/* static */ List<WarheadType> WarheadType::Array;

WarheadType::WarheadType(const std::string& id)
:AbstractType(id)
{
}

void WarheadType::loadRules(INIFile* file)
{
	INISection* section = file->getSection(ID);
	if (!section) return;

	AbstractType::loadRules(file);

	allocateList(Animation::Array, section->readStringValue("AnimList"));
	allocateList(VoxelAnimType::Array, section->readStringValue("DebrisTypes"));
}

void WarheadType::loadArt(INIFile* file)
{
	INISection* section = file->getSection(ID);
	if (!section) return;

	AbstractType::loadArt(file);

}