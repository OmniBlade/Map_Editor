#include "stdafx.h"
#include "Theater.hpp"
#include <iostream>
#include <sstream>
#include "../../../Editor.FileSystem/INIFile/INIFile.hpp"
#include "../../../Editor.FileSystem/INIFile/INISection.hpp"
#include "../../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../../Log.hpp"

Theater::Theater(const std::string& file)
{
	controlFile = INIManager::instance()->get(file);
	if (!controlFile)
	{
		Log::line("THEATER - Unable to get control file with name: " + file, Log::DEBUG);
		return;
	}
	
	readGeneral();
	readTileSets();
}


Theater::~Theater()
{
}

void Theater::readGeneral()
{
	INISection* general = controlFile->getSection("General");
	if (general)
	{
		general->readIntValue("RampBase", RampBase);
		general->readIntValue("RampSmooth", RampSmooth);
		general->readIntValue("MMRampBase", MMRampBase);
		general->readIntValue("ClearTile", ClearTile);
		general->readIntValue("RoughTile", RoughTile);
		general->readIntValue("ClearToRoughLat", ClearToRoughLat);
		general->readIntValue("SandTile", SandTile);
		general->readIntValue("ClearToSandLat", ClearToSandLat);
		general->readIntValue("GreenTile", GreenTile);
		general->readIntValue("ClearToGreenLat", ClearToGreenLat);
		general->readIntValue("PaveTile", PaveTile);
		general->readIntValue("MiscPaveTile", MiscPaveTile);
		general->readIntValue("ClearToPaveLat", ClearToPaveLat);
		general->readIntValue("HeightBase", HeightBase);
		general->readIntValue("BlackTile", BlackTile);
		general->readIntValue("CliffSet", CliffSet);
		general->readIntValue("ShorePieces", ShorePieces);
		general->readIntValue("WaterSet", WaterSet);
		general->readIntValue("Ice1Set", Ice1Set);
		general->readIntValue("Ice2Set", Ice2Set);
		general->readIntValue("IceShoreSet", IceShoreSet);
		general->readIntValue("BridgeSet", BridgeSet);
		general->readIntValue("WoodBridgeSet", WoodBridgeSet);
		general->readIntValue("TrainBridgeSet", TrainBridgeSet);
		general->readIntValue("SlopeSetPieces", SlopeSetPieces);
		general->readIntValue("SlopeSetPieces2", SlopeSetPieces2);
		general->readIntValue("MonorailSlopes", MonorailSlopes);
		general->readIntValue("Tunnels", Tunnels); //Animated
		general->readIntValue("TrackTunnels", TrackTunnels); //Animated
		general->readIntValue("DirtTunnels", DirtTunnels); //Animated
		general->readIntValue("DirtTrackTunnels", DirtTrackTunnels); //Animated
		general->readIntValue("WaterfallEast", WaterfallEast); //Animated
		general->readIntValue("WaterfallWest", WaterfallWest); //Animated
		general->readIntValue("WaterfallNorth", WaterfallNorth); //Animated
		general->readIntValue("WaterfallSouth", WaterfallSouth); //Animated
		general->readIntValue("CliffRamps", CliffRamps);
		general->readIntValue("PavedRoads", PavedRoads);
		general->readIntValue("PavedRoadEnds", PavedRoadEnds);
		general->readIntValue("Medians", Medians);	//Nice word for paved road bits
		general->readIntValue("RoughGround", RoughGround);
		general->readIntValue("DirtRoadJunction", DirtRoadJunction);
		general->readIntValue("DirtRoadCurve", DirtRoadCurve);
		general->readIntValue("DirtRoadStraight", DirtRoadStraight);
		general->readIntValue("BridgeTopLeft1", BridgeTopLeft1);
		general->readIntValue("BridgeTopLeft2", BridgeTopLeft2);
		general->readIntValue("BridgeBottomRight1", BridgeBottomRight1);
		general->readIntValue("BridgeBottomRight2", BridgeBottomRight2);
		general->readIntValue("BridgeTopRight1", BridgeTopRight1);
		general->readIntValue("BridgeTopRight2", BridgeTopRight2);
		general->readIntValue("BridgeBottomLeft1", BridgeBottomLeft1);
		general->readIntValue("BridgeBottomLeft2", BridgeBottomLeft2);
		general->readIntValue("BridgeMiddle1", BridgeMiddle1);
		general->readIntValue("BridgeMiddle2", BridgeMiddle2);
		general->readIntValue("DestroyableCliffs", DestroyableCliffs);
		general->readIntValue("WaterCliffs", WaterCliffs);
		general->readIntValue("WaterCaves", WaterCaves);
		general->readIntValue("PavedRoadSlopes", PavedRoadSlopes);
		general->readIntValue("DirtRoadSlopes", DirtRoadSlopes);
		general->readIntValue("WaterBridge", WaterBridge);
	}
	else
		std::cout << "[General] does not exist in the file!" << std::endl;
}

void Theater::readTileSets()
{
	Log::timerStart();
	std::string tileset = "TileSet";
	std::stringstream setNumber;
	for (unsigned int i = 0; i < 9999; ++i)
	{
		//if (i == 19)
//			std::cout << "";

		if (i < 10)
			setNumber << "0";
		if (i < 100)
			setNumber << "0";
		if (i < 1000)
			setNumber << "0";
		setNumber << i;

		if (INISection* ret = controlFile->getSection(tileset + setNumber.str()))
			tileSets.push_back(std::make_unique<TileSet>(i, ret));
		else
		{
			break; //Loop until done
		}

		setNumber.str(std::string());
	}

	Log::line("Parsing Theater Control File took: " + Log::getTimerValue(), Log::DEBUG);
}