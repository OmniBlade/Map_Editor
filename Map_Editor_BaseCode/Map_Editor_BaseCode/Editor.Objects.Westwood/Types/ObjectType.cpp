#include "stdafx.h"
#include "ObjectType.hpp"


ObjectType::ObjectType(const std::string& id)
:AbstractType(id)
{

}

void ObjectType::loadRules(INIFile* rules)
{
	AbstractType::loadRules(rules);
	INISection* rulesSection = rules->getSection(ID);
	Image = rulesSection->readStringValue("Image", Image);
	AlphaImage = rulesSection->readStringValue("AlphaImage", AlphaImage);
}

void ObjectType::loadArt(INIFile* art)
{
	AbstractType::loadArt(art);
	INISection* artSection = art->getSection(ID);
	Theater = artSection->readBoolValue("Theater", false);
	NewTheater = artSection->readBoolValue("NewTheater", false);
	Voxel = artSection->readBoolValue("Voxel", false);
}
