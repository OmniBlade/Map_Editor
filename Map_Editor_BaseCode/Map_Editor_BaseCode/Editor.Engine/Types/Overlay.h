#pragma once
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
#include "Managers\ObjectList.hpp"

class OverlayType;

class Overlay
{
public:
	static ObjectList<Overlay> Array;

	Overlay();
	Overlay(int x, int y, int overlayIndex, int overlayFrame);
	


	Vector2D loc;
	OverlayType* pOverlayType;
	int overlayIndex, overlayFrame;
};

