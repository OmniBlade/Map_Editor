#pragma once
#include "../Map/TileSet.hpp"
#include <vector>
#include <memory>

class INIFile;

class Theater
{
public:
	Theater(const std::string& file);
	~Theater();

	/*
		Reads the [General] section of the theater control file
	*/
	void readGeneral();
	
	/* 
		Reads the tilesets defined in the control file, range is from 0000 to 9999
		Creates a TileSet object for each found TileSet
	*/
	void readTileSets();

	int RampBase= -1;
	int RampSmooth= -1;
	int MMRampBase= -1;
	int ClearTile= -1;
	int RoughTile= -1;
	int ClearToRoughLat= -1;
	int SandTile= -1;
	int ClearToSandLat= -1;
	int GreenTile= -1;
	int ClearToGreenLat= -1;
	int PaveTile= -1;
	int MiscPaveTile= -1;
	int ClearToPaveLat= -1;
	int HeightBase= -1;
	int BlackTile= -1;
	int CliffSet= -1;
	int ShorePieces= -1;
	int WaterSet= -1;
	int Ice1Set= -1;
	int Ice2Set= -1;
	int IceShoreSet= -1;
	int BridgeSet= -1;
	int WoodBridgeSet= -1;
	int TrainBridgeSet= -1;
	int SlopeSetPieces= -1;
	int SlopeSetPieces2= -1;
	int MonorailSlopes= -1;
	int Tunnels= -1;
	int TrackTunnels= -1;
	int DirtTunnels= -1;
	int DirtTrackTunnels= -1;
	int WaterfallEast= -1;
	int WaterfallWest= -1;
	int WaterfallNorth= -1;
	int WaterfallSouth= -1;
	int CliffRamps= -1;
	int PavedRoads= -1;
	int PavedRoadEnds= -1;
	int Medians= -1;
	int RoughGround= -1;
	int DirtRoadJunction= -1;
	int DirtRoadCurve= -1;
	int DirtRoadStraight= -1;
	int BridgeTopLeft1= -1;
	int BridgeTopLeft2= -1;
	int BridgeBottomRight1= -1;
	int BridgeBottomRight2= -1;
	int BridgeTopRight1= -1;
	int BridgeTopRight2= -1;
	int BridgeBottomLeft1= -1;
	int BridgeBottomLeft2= -1;
	int BridgeMiddle1= -1;
	int BridgeMiddle2= -1;
	int DestroyableCliffs= -1;
	int WaterCliffs= -1;
	int WaterCaves= -1;
	int PavedRoadSlopes= -1;
	int DirtRoadSlopes= -1;
	int WaterBridge= -1;

private:
	INIFile* controlFile;
	std::vector<std::unique_ptr<TileSet>> tileSets;
};

