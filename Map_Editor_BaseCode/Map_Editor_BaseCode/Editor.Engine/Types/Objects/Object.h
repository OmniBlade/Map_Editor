#pragma once
#include "../../Map/Cells/CellStruct.h"

class LineSplitter;
class ObjectType;

class Object
{
public:
	Object();
	Object(short x, short y);
	void setObjectType(ObjectType* pType) { pObjectType = pType; };

	CellStruct MapCoords;
	ObjectType* pObjectType;
};

