#include "stdafx.h"
#include "ParticleType.hpp"
#include "../../Log.hpp"
#include "WarheadType.hpp"

/* static */ List<ParticleType> ParticleType::Array;

ParticleType::ParticleType(const std::string& id)
:ObjectType(id)
{
}

void ParticleType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);
	WarheadType::Array.findOrAllocate(rulesSection->readStringValue("Warhead"));
}

void ParticleType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;
	ObjectType::loadArt(art);
}