#pragma once

#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/TmpFile/TMPFile.hpp"
#include <string>
#include <vector>
#include <memory>

class TileSet
{
public:
	TileSet(int _ID, INISection* _section);
	~TileSet();

	/*
		Parses the INI section for the tileset and reads its values
	*/
	void parse();
	
	/*
		Collects the tiles for the tileset instance and pushes them into a vector
	*/
	void collectTiles();

	/*
		Because there's little documentation on Theater control files, lots of comments are to be expected here
		It's mainly for general understanding
	*/

	int ID;						// The ID of the tileset, like 14
	std::string FileName;		// WARNING! Westwood strncpy's 0xE bytes into this buffer without NULL terminating it.
	std::string SetName;
	int TilesInSet = 0;			// Defines the number of tiles in the set, nothing more should be read
	short LastTilesInSet = -1;		// Probably unused. Defines what the last TilesInSet value used to be, something about clean up etc
	int MarbleMadnessTile = -1;		// The ID of a NORMAL tileset used in Marble Madness / Framework mode
	int NonMarbleMadnessTile = -1;	// The ID of a MARBLE MADNESS tileset used for switching back to normal view
	int ToSnowTheater;			// Unused, used to define the corresponding tileset used in theater (eg grass -> snowy grass)
	int ToTemperateTheater;		// Unused, see above
	int TileAnimIndex = -1;			// Tile%02dAnim, actually an AnimTypeClass array index...
	int TileXOffset = 0;			// Tile%02dXOffset
	int TileYOffset = 0;			// Tile%02dYOffset
	int TileAttachesTo = 0;			// Tile%02dAttachesTo, iso tile index?
	int TileZAdjust = 0;			// Tile%02dZAdjust
	bool Morphable;				// Whether the tileset can be changed with the tool to raise/lower terrain (like normal grass becoming a ramp
	bool ShadowCaster;			// Whether the tileset (CLIFF specifically) casts a shadow. Only works if in [General]->CliffSet is set to its ID
	bool AllowToPlace = true;			// Defines whether the tiles in this tileset can be placed (in editor)
	bool AllowTiberium;			// Whether tiberium can be placed on this (Tiberium on ramps causes Internal ERRORSs :D)

private:
	INISection* section;
	std::vector<std::unique_ptr<TMPFile>> tiles;
};

