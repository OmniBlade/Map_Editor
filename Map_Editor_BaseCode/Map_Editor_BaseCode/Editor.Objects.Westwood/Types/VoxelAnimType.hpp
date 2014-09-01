#pragma once

#include "../Managers/WWList.hpp"
#include "ObjectType.hpp"

class VoxelAnimType : public ObjectType //Was Animation, but since nothing is renderd anyhow, skip to ObjectType
{
public:
	static WWList<VoxelAnimType> Array;
	VoxelAnimType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string Warhead;
};

