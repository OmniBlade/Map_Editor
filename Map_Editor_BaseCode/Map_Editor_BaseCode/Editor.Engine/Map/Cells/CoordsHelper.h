#include "CoordsStruct.h"
#include "CellStruct.h"

CoordsStruct cell2Coords(CellStruct& cStruct)
{
	CoordsStruct coords;
	//CoordStruct = CellX * 256 + 128, CellY * 256 + 128, 0

	coords.X = cStruct.X * 256 + 128;
	coords.Y = cStruct.Y * 256 + 128;
	coords.Z = 0;

	return coords;
}

CellStruct coords2Cell(CoordsStruct& cStruct)
{
	CellStruct cell;
	//CellStruct = CoordsX >> 8, CoordsY >> 8

	cell.X = cStruct.X >> 8;
	cell.Y = cStruct.Y >> 8;

	return cell;
}