#pragma once

#include "../Managers/List.hpp"
#include "ObjectType.hpp"

class ParticleType : public ObjectType
{
public:
	static List<ParticleType> Array;
	ParticleType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;
};

