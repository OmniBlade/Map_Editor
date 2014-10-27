#include "stdafx.h"
#include "Object.h"
#include "../../../Editor.Objects.Westwood/Types/ObjectType.hpp"

Object::Object()
{

}

Object::Object(short x, short y)
{
	MapCoords.X = x;
	MapCoords.Y = y;
}

