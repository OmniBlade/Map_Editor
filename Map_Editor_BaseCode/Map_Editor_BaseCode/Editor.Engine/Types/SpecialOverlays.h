#include "stdafx.h"
#include "Overlay.h"

class SpecialOverlays
{

private:
	/* == WALLS == */
	/*
		Purely used for WallTower and Gates!
		These 3 are the ONLY types that will connect to the gates and towers!
		Ares won't change this anytime soon because everything is hardcoded even deeper (even NS/EW gate code)
	*/

	static const byte IDX_GASAND = 0x00;	// Sandbag
	static const byte IDX_GAWALL = 0x02;	// Allied/GDI wall
	static const byte IDX_NAWALL = 0x1A;	// Soviet/NOD wall

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

	These MUST be consecutive!

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
	static const byte IDX_BRIDGEB1 = 0xED;	// High-wooden bridge - These replace TS' track bridge in-game
	static const byte IDX_BRIDGEB2 = 0xEE;	// High-wooden bridge - These replace TS' track bridge in-game
	static const byte IDX_RAILBRDG1 = 0x3B;	// High-tracks bridge - Overlay exists, bridgehead doesn't
	static const byte IDX_RAILBRDG2 = 0x3C;	// High-tracks bridge - Overlay exists, bridgehead doesn't

	static const byte IDX_LOBRIDGE1 = 0x7A;	// Low bridge end 1 Concrete?
	static const byte IDX_LOBRIDGE2 = 0x7B;	// Low bridge end 2 Concrete?
	static const byte IDX_LOBRIDGE3 = 0x7C;	// Low bridge end 3 Concrete?
	static const byte IDX_LOBRIDGE4 = 0x7D;	// Low bridge end 4 Concrete?

	static const byte IDX_LOBRDGB_MIN = 0xCD; // Low-Concrete bridge 01
	static const byte IDX_LOBRDGB_MAX = 0xE8; // Low-Concrete bridge 28
	static const byte IDX_LOBRDG_MIN = 0x4A;  // Low-Wooden bridge 01
	static const byte IDX_LOBRDG_MAX = 0x65;  // Low-Wooden bridge 28

public:
	
	static bool isRiparius(Overlay* pOverlay) 
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex >= IDX_RIPARIUS_MIN && pOverlay->overlayIndex <= IDX_RIPARIUS_MAX);
	}

	static bool isCruentus(Overlay* pOverlay) 
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex >= IDX_CRUENTUS_MIN && pOverlay->overlayIndex <= IDX_CRUENTUS_MAX;
	}

	static bool isVinifera(Overlay* pOverlay) 
	{
		if (!pOverlay) return false;
		
		return pOverlay->overlayIndex >= IDX_VINIFERA_MIN && pOverlay->overlayIndex <= IDX_VINIFERA_MAX;
	}

	static bool isAboreus(Overlay* pOverlay) {
		if (!pOverlay) return false;

		return pOverlay->overlayIndex >= IDX_ABOREUS_MIN && pOverlay->overlayIndex <= IDX_ABOREUS_MAX;
	}

	static bool isHighBridge(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex == IDX_BRIDGE1 || pOverlay->overlayIndex == IDX_BRIDGE2
			|| pOverlay->overlayIndex == IDX_BRIDGEB1 || pOverlay->overlayIndex == IDX_BRIDGEB2;
	}

	static bool isLowBridge(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return isLowConcreteBridge(pOverlay) || isLowWoodenBridge(pOverlay);
	}

	/*
		Can a gate connect to this overlay (hardcoded walls only)?
	*/
	static bool canGateConnect(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex == IDX_GASAND || pOverlay->overlayIndex == IDX_GAWALL || pOverlay->overlayIndex == IDX_NAWALL;
	}

	/*
		Can a wall tower connect to this overlay (hardcoded walls only)?
		Eat shit NAWALL, you can't connect to a WallTower. Don't ask me, WW did this
	*/
	static bool canWallTowerConnect(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex == IDX_GASAND || pOverlay->overlayIndex == IDX_GAWALL;
	}

	static bool isLowConcreteBridge(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex >= IDX_LOBRDGB_MIN && pOverlay->overlayIndex <= IDX_LOBRDGB_MAX;
	}

	static bool isLowWoodenBridge(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex >= IDX_LOBRDG_MIN && pOverlay->overlayIndex <= IDX_LOBRDG_MAX;
	}

	static bool isTrackBridge(Overlay* pOverlay)
	{
		if (!pOverlay) return false;

		return pOverlay->overlayIndex == IDX_RAILBRDG1 || pOverlay->overlayIndex == IDX_RAILBRDG2;
	}
};