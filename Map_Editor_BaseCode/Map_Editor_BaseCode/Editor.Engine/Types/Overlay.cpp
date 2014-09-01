#include "stdafx.h"
#include "Overlay.h"

/* static */ MapObjectList<Overlay> Overlay::Array;

Overlay::Overlay()
{
}

Overlay::Overlay(int x, int y, int overlayIndex, int overlayFrame)
:overlayIndex(overlayIndex), overlayFrame(overlayFrame)
{
	loc.x = x;
	loc.y = y;
}