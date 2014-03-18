#pragma once

#include "../../Editor.FileSystem/INIFile/INIFile.hpp"
#include "../../Editor.FileSystem/INIFile/INISection.hpp"

class Theater
{
public:
	Theater(INIFile* _controlFile);
	~Theater();

	void readGeneral();

	short RampBase;
	short RampSmooth;
	short MMRampBase;
	short ClearTile;
	short RoughTile;
	short ClearToRoughLat;
	short SandTile;
	short ClearToSandLat;
	short GreenTile;
	short ClearToGreenLat;
	short PaveTile;
	short MiscPaveTile;
	short ClearToPaveLat;
	short HeightBase;
	short BlackTile;
	short CliffSet;
	short ShorePieces;
	short WaterSet;
	short Ice1Set;
	short Ice2Set;
	short IceShoreSet;
	short BridgeSet;
	short WoodBridgeSet;
	short TrainBridgeSet;
	short SlopeSetPieces;
	short SlopeSetPieces2;
	short MonorailSlopes;
	short Tunnels;
	short TrackTunnels;
	short DirtTunnels;
	short DirtTrackTunnels;
	short WaterfallEast;
	short WaterfallWest;
	short WaterfallNorth;
	short WaterfallSouth;
	short CliffRamps;
	short PavedRoads;
	short PavedRoadEnds;
	short Medians;
	short RoughGround;
	short DirtRoadJunction;
	short DirtRoadCurve;
	short DirtRoadStraight;
	short BridgeTopLeft1;
	short BridgeTopLeft2;
	short BridgeBottomRight1;
	short BridgeBottomRight2;
	short BridgeTopRight1;
	short BridgeTopRight2;
	short BridgeBottomLeft1;
	short BridgeBottomLeft2;
	short BridgeMiddle1;
	short BridgeMiddle2;
	short DestroyableCliffs;
	short WaterCliffs;
	short WaterCaves;
	short PavedRoadSlopes;
	short DirtRoadSlopes;
	short WaterBridge;

private:
	INIFile* controlFile;
};

