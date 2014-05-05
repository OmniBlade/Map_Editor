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
	rulesSection->readStringValue("Image", Image, ID);
	rulesSection->readStringValue("AlphaImage", AlphaImage);
}

void ObjectType::loadArt(INIFile* art)
{
	AbstractType::loadArt(art);
	INISection* artSection = art->getSection(ID);
	artSection->readBoolValue("Theater", Theater);
	artSection->readBoolValue("NewTheater",  NewTheater);
	artSection->readBoolValue("Voxel", Voxel);
}
