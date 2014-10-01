#include "stdafx.h"
#include "TileSet.hpp"
#include <iostream>
#include <sstream>
#include "../Map/TheaterCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/TMPManager.hpp"
/*
	NOTE: Not sure where to place this yet, it's just working ahead really...
*/

TileSet::TileSet(int _ID, INISection* _section)
:ID(_ID), section(_section)
{
	std::cout << "---------------------------------------------\nParsing tileset with ID: " << ID << std::endl;
	//std::cout << "Name: " << section->sectionName << " current theater extension: " << TheaterCollection::getInstance()->getCurrent()->TileExtension << std::endl;
	parse();
	collectTiles();
}


TileSet::~TileSet()
{
}

void TileSet::parse()
{
	if (section)
	{
		section->readStringValue("FileName", FileName);
		section->readStringValue("SetName", SetName);
		section->readIntValue("TilesInSet", TilesInSet);
		section->readIntValue("MarbleMadness", MarbleMadnessTile);
		section->readIntValue("NonMarbleMadness", NonMarbleMadnessTile);
		section->readIntValue("TileAnimIndex", TileAnimIndex);
		section->readIntValue("TileXOffset", TileXOffset);
		section->readIntValue("TileYOffset", TileYOffset);
		section->readIntValue("TileAttachesTo", TileAttachesTo);
		section->readIntValue("TileZAdjust", TileZAdjust);
		section->readBoolValue("Morphable", Morphable);
		section->readBoolValue("ShadowCaster", ShadowCaster);
		section->readBoolValue("AllowToPlace", AllowToPlace);
		section->readBoolValue("AllowTiberium", AllowTiberium);
	}
	else
		std::cout << "Tileset with ID " << ID << " does not exist!" << std::endl;	
}


void TileSet::collectTiles()
{
	std::string& extension = TheaterCollection::getInstance()->getCurrent()->TileExtension;
	std::stringstream number;
	
	for (int i = 1; i <= TilesInSet; ++i)
	{
		if (i < 10)
			number << '0';
		if (i > 99)
		{
			std::cout << "More than 99 tiles were found in this set, only 00-99 can exist!" << std::endl;
			break;
		}
		number << i;

		if (TMPManager::instance()->get(FileName + number.str() + '.' + extension))
		{
			//tiles.push_back(TMPManager::instance()->get(FileName + number.str() + (char)i + '.' + extension));
			std::cout << "Hey there, should the tiles be pushed into the tiles vector in collectTiles()?" << std::endl;
			
			//Search for a-b-c-d-e-f-g
			for (unsigned int i = 65; i < 72; ++i) // ASCII 65 -> A, 72 -> H (loop until 71, G)
			{
				if (!TMPManager::instance()->get(FileName + number.str() + (char)i + '.' + extension))
					break;
				else
				{
					//tiles.push_back(TMPManager::instance()->get(FileName + number.str() + (char)i + '.' + extension));
				}
				//else
					//std::cout << "Now parsing: " << FileName << number.str() << (char)i << '.' << TheaterCollection::getInstance()->getCurrent()->TileExtension << std::endl;
			}
		}
		else
			break;

		number.str(std::string());
	}
	//std::cout << "Tiles collected for set: " << SetName << " (" << FileName << ")" << std::endl;
}

/*
[23:51:44] <Starkku> It serves different purpose in bridges
[23:51:55] <Starkku> It works for everything else too but it does different thing
[23:51:55] <@RP> Okay, but it works for anything else
[23:52:42] <@RP> Okay, for now it's just reading them so I'll create a function that looks for fileName + X (0 <= X <= 99) and a-z
[23:52:51] <Starkku> alright
[23:54:07] <Starkku> For tiles other than bridgeheads the lettered ones are basically variants that game randomly substitutes the non-lettered one with
[23:54:13] <Starkku> As far as I know
[23:54:41] <Starkku> And it only goes up to g as far as I know
[23:54:50] <Starkku> Rest of the letters won't work
[23:56:32] <Starkku> Well combined with the non-lettered one
[23:56:35] <Starkku> That makes 8 variants
*/