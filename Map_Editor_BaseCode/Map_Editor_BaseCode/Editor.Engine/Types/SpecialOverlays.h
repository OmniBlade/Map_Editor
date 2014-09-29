#include "stdafx.h"
#include "Overlay.h"

class SpecialOverlays
{

private:
	/* == WALLS == */
	/*
	
	*/

	static const byte IDX_GASAND = 0x00;	// Sandbag
	static const byte IDX_GAWALL = 0x02;	// Allied wall
	static const byte IDX_NAWALL = 0x1A;	// Soviet wall

	/* == VEINHOLE == */
	/*
		Although not loaded, still valid declarations
	*/	

	static const byte IDX_VEINS = 0x7E;			// Veins
	static const byte IDX_VEINHOLE = 0xA7;		// Veinhole
	static const byte IDX_VEINHOLEDUMMY = 0xB2;	// Veinhole dummy


	/* == TIBERIUMS == */
	/*
	Riparius = 1
	Cruentus = 2
	Vinifera = 3
	Aboreus = 4

	Err... These appear to be the same for both Red Alert 2 and Yuri's Revenge
	*/

	static const byte IDX_RIPARIUS_MIN = 0x66;	// Ore
	static const byte IDX_RIPARIUS_MAX = 0x79;	// Ore
	static const byte IDX_CRUENTUS_MIN = 0x1B;	// Gems
	static const byte IDX_CRUENTUS_MAX = 0x26;	// Gems
	static const byte IDX_VINIFERA_MIN = 0x7F;
	static const byte IDX_VINIFERA_MAX = 0x92;
	static const byte IDX_ABOREUS_MIN = 0x93;
	static const byte IDX_ABOREUS_MAX = 0xA6;

	/* == BRIDGES == */
	/*
	Err... These appear to be the same for both Red Alert 2 and Yuri's Revenge
	*/
	static const byte IDX_BRIDGE1 = 0x18;	// High-concrete bridge
	static const byte IDX_BRIDGE2 = 0x19;	// High-concrete bridge
	static const byte IDX_BRIDGEB1 = 0xED;	// High-wooden bridge
	static const byte IDX_BRIDGEB2 = 0xEE;	// High-wooden bridge
	static const byte IDX_RAILBRDG1 = 0x3B;	// High-tracks bridge
	static const byte IDX_RAILBRDG2 = 0x3C;	// High-tracks bridge

	static const byte IDX_LOBRIDGE1 = 0x7A;	// Low bridge 1 Concrete?
	static const byte IDX_LOBRIDGE2 = 0x7B;	// Low bridge 2 Concrete?
	static const byte IDX_LOBRIDGE3 = 0x7C;	// Low bridge 3 Concrete?
	static const byte IDX_LOBRIDGE4 = 0x7D;	// Low bridge 4 Concrete?

public:
	
	static bool isRiparius(Overlay* pOverlay) {
		if (!pOverlay)
			return false;

		if (pOverlay->overlayIndex <= IDX_RIPARIUS_MIN && pOverlay->overlayIndex <= IDX_RIPARIUS_MAX) { return true; } return false;
	}

	static bool isCruentus(Overlay* pOverlay) {
		if (!pOverlay)
			return false;

		if (pOverlay->overlayIndex <= IDX_CRUENTUS_MIN && pOverlay->overlayIndex <= IDX_CRUENTUS_MAX) { return true; } return false;
	}

	static bool isVinifera(Overlay* pOverlay) {
		if (!pOverlay)
			return false;
		
		if (pOverlay->overlayIndex <= IDX_VINIFERA_MIN && pOverlay->overlayIndex <= IDX_VINIFERA_MAX) { return true; } return false;
	}

	static bool isAboreus(Overlay* pOverlay) {
		if (!pOverlay)
			return false;

		if (pOverlay->overlayIndex <= IDX_ABOREUS_MIN && pOverlay->overlayIndex <= IDX_ABOREUS_MAX) { return true; } return false;
	}

	static bool isHighBridge(Overlay* pOverlay)
	{
		if (!pOverlay)
			return false;

		if (pOverlay->overlayIndex == IDX_BRIDGE1 || pOverlay->overlayIndex == IDX_BRIDGE2
			|| pOverlay->overlayIndex == IDX_BRIDGEB1 || pOverlay->overlayIndex == IDX_BRIDGEB2)
			return true;
		return false;
	}

	static bool isTrackBridge(Overlay* pOverlay)
	{
		if (!pOverlay)
			return false;

		if (pOverlay->overlayIndex == IDX_RAILBRDG1 || pOverlay->overlayIndex == IDX_RAILBRDG2)
			return true;
		return false;
	}
};