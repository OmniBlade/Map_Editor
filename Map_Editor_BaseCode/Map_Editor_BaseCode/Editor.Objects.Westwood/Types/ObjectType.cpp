#include "stdafx.h"
#include "ObjectType.hpp"


ObjectType::ObjectType(INISection* _rulesSection, INISection* _artSection)
:AbstractType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
	
}

void ObjectType::loadRules()
{
	Image = rulesSection->readStringValue("Image", "");
	AlphaImage = rulesSection->readStringValue("AlphaImage", "");
}

void ObjectType::loadArt()
{
	Theater = artSection->readBoolValue("Theater", false);
	NewTheater = artSection->readBoolValue("NewTheater", false);
	Voxel = artSection->readBoolValue("Voxel", false);
}
