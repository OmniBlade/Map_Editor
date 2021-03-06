#include "stdafx.h"
#include "VoxelAnimType.hpp"
#include "../../Log.hpp"
#include "WarheadType.hpp"

/* static */ WWList<VoxelAnimType> VoxelAnimType::Array;

VoxelAnimType::VoxelAnimType(const std::string& id)
:ObjectType(id)
{

}

void VoxelAnimType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);
	rulesSection->readStringValue("Warhead", Warhead);
	WarheadType::Array.findOrAllocate(Warhead);
}

void VoxelAnimType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}