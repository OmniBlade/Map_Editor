#pragma once
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
#include "Managers\MapObjectList.hpp"

class OverlayType;

class Overlay
{
public:
	static MapObjectList<Overlay> Array;

	Overlay();
	Overlay(int x, int y, byte overlayIndex, byte overlayFrame);

	Vector2D loc;
	OverlayType* pOverlayType;
	byte overlayIndex, overlayFrame;
};

