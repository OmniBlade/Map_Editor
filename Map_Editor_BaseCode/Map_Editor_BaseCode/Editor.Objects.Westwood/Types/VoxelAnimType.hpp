#pragma once

#include "../Managers/List.hpp"
#include "ObjectType.hpp"

class VoxelAnimType : public ObjectType //Was Animation, but since nothing is renderd anyhow, skip to ObjectType
{
public:
	static List<VoxelAnimType> Array;
	VoxelAnimType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;
};

