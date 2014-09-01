#pragma once

#include "../Managers/WWList.hpp"
#include "ObjectType.hpp"

class ParticleType : public ObjectType
{
public:
	static WWList<ParticleType> Array;
	ParticleType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string Warhead;
};

