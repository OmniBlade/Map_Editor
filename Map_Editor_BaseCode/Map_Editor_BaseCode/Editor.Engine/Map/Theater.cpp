#include "stdafx.h"
#include "Theater.hpp"
#include <iostream>

Theater::Theater(INIFile* _controlFile)
:controlFile(_controlFile)
{
	readGeneral();
}


Theater::~Theater()
{
}

void Theater::readGeneral()
{
	INISection* general = controlFile->getSection("General");
	if (general)
	{
		RampBase = general->readIntValue("RampBase", -1);
		RampSmooth = general->readIntValue("RampSmooth", -1);
		MMRampBase = general->readIntValue("MMRampBase", -1);
		ClearTile = general->readIntValue("ClearTile", -1);
		RoughTile = general->readIntValue("RoughTile", -1);
		ClearToRoughLat = general->readIntValue("ClearToRoughLat", -1);
		SandTile = general->readIntValue("SandTile", -1);
		ClearToSandLat = general->readIntValue("ClearToSandLat", -1);
		GreenTile = general->readIntValue("GreenTile", -1);
		ClearToGreenLat = general->readIntValue("ClearToGreenLat", -1);
		PaveTile = general->readIntValue("PaveTile", -1);
		MiscPaveTile = general->readIntValue("MiscPaveTile", -1);
		ClearToPaveLat = general->readIntValue("ClearToPaveLat", -1);
		HeightBase = general->readIntValue("HeightBase", -1);
		BlackTile = general->readIntValue("BlackTile", -1);
		CliffSet = general->readIntValue("CliffSet", -1);
		ShorePieces = general->readIntValue("ShorePieces", -1);
		WaterSet = general->readIntValue("WaterSet", -1);
		Ice1Set = general->readIntValue("Ice1Set", -1);
		Ice2Set = general->readIntValue("Ice2Set", -1);
		IceShoreSet = general->readIntValue("IceShoreSet", -1);
		BridgeSet = general->readIntValue("BridgeSet", -1);
		WoodBridgeSet = general->readIntValue("WoodBridgeSet", -1);
		TrainBridgeSet = general->readIntValue("TrainBridgeSet", -1);
		SlopeSetPieces = general->readIntValue("SlopeSetPieces", -1);
		SlopeSetPieces2 = general->readIntValue("SlopeSetPieces2", -1);
		MonorailSlopes = general->readIntValue("MonorailSlopes", -1);
		Tunnels = general->readIntValue("Tunnels", -1);
		TrackTunnels = general->readIntValue("TrackTunnels", -1);
		DirtTunnels = general->readIntValue("DirtTunnels", -1);
		DirtTrackTunnels = general->readIntValue("DirtTrackTunnels", -1);
		WaterfallEast = general->readIntValue("WaterfallEast", -1);
		WaterfallWest = general->readIntValue("WaterfallWest", -1);
		WaterfallNorth = general->readIntValue("WaterfallNorth", -1);
		WaterfallSouth = general->readIntValue("WaterfallSouth", -1);
		CliffRamps = general->readIntValue("CliffRamps", -1);
		PavedRoads = general->readIntValue("PavedRoads", -1);
		PavedRoadEnds = general->readIntValue("PavedRoadEnds", -1);
		Medians = general->readIntValue("Medians", -1);
		RoughGround = general->readIntValue("RoughGround", -1);
		DirtRoadJunction = general->readIntValue("DirtRoadJunction", -1);
		DirtRoadCurve = general->readIntValue("DirtRoadCurve", -1);
		DirtRoadStraight = general->readIntValue("DirtRoadStraight", -1);
		BridgeTopLeft1 = general->readIntValue("BridgeTopLeft1", -1);
		BridgeTopLeft2 = general->readIntValue("BridgeTopLeft2", -1);
		BridgeBottomRight1 = general->readIntValue("BridgeBottomRight1", -1);
		BridgeBottomRight2 = general->readIntValue("BridgeBottomRight2", -1);
		BridgeTopRight1 = general->readIntValue("BridgeTopRight1", -1);
		BridgeTopRight2 = general->readIntValue("BridgeTopRight2", -1);
		BridgeBottomLeft1 = general->readIntValue("BridgeBottomLeft1", -1);
		BridgeBottomLeft2 = general->readIntValue("BridgeBottomLeft2", -1);
		BridgeMiddle1 = general->readIntValue("BridgeMiddle1", -1);
		BridgeMiddle2 = general->readIntValue("BridgeMiddle2", -1);
		DestroyableCliffs = general->readIntValue("DestroyableCliffs", -1);
		WaterCliffs = general->readIntValue("WaterCliffs", -1);
		WaterCaves = general->readIntValue("WaterCaves", -1);
		PavedRoadSlopes = general->readIntValue("PavedRoadSlopes", -1);
		DirtRoadSlopes = general->readIntValue("DirtRoadSlopes", -1);
		WaterBridge = general->readIntValue("WaterBridge", -1);
	}
	else
		std::cout << "[General] does not exist in the file!" << std::endl;
}