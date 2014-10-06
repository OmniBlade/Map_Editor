#include "stdafx.h"
#include "OverlayTypeValidator.h"
#include "Types\OverlayType.hpp"
#include "../Editor.Engine/Types/SpecialOverlays.h"
#include "../Log.hpp"
#include <sstream>

OverlayTypeValidator::OverlayTypeValidator()
{
	if (Config::explicitOverlayTypeValidation)
	{
		Log::line();
		Log::line("Validating extremely hardcoded OverlayType indexes below.", Log::DEBUG);

		validateWalls();
		validateBridges();
		validateTracks();
		validateTiberiums();
		validateVeinhole();
		dumpOverlayTypes();

		Log::line("Validating OverlayType indexes done, if there's nothing to see, all is fine.", Log::DEBUG);
		Log::line();
	}
}

void OverlayTypeValidator::validateWalls()
{
	OverlayType* pGawall = OverlayType::Array.get(SpecialOverlays::IDX_GAWALL);
	OverlayType* pGasand = OverlayType::Array.get(SpecialOverlays::IDX_GASAND);
	OverlayType* pNawall = OverlayType::Array.get(SpecialOverlays::IDX_NAWALL);

	if (pGasand && !pGasand->Wall)
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_GASAND) 
			+ " is supposed to be a Wall! It's used for Gate and WallTower connection!", Log::DEBUG);
	}


	if (pGawall && !pGawall->Wall)
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_GAWALL)
			+ " is supposed to be a Wall! It's used for Gate and WallTower connection!", Log::DEBUG);
	}


	if (pNawall && !pNawall->Wall)
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_NAWALL) 
			+ " is supposed to be a Wall! It's used for Gate connection!", Log::DEBUG);
	}
}

void OverlayTypeValidator::validateTiberiums()
{
	validateConsecutive("Riparius", SpecialOverlays::IDX_RIPARIUS_MIN, SpecialOverlays::IDX_RIPARIUS_MAX, 20);
	validateConsecutive("Cruentus", SpecialOverlays::IDX_CRUENTUS_MIN, SpecialOverlays::IDX_CRUENTUS_MAX, 12);
	validateConsecutive("Vinifera", SpecialOverlays::IDX_VINIFERA_MIN, SpecialOverlays::IDX_VINIFERA_MAX, 20);
	validateConsecutive("Aboreus", SpecialOverlays::IDX_ABOREUS_MIN, SpecialOverlays::IDX_ABOREUS_MAX, 20);
}

void OverlayTypeValidator::validateBridges()
{
	validateConsecutive("Low-Concrete Bridge", SpecialOverlays::IDX_LOBRDB_MIN, SpecialOverlays::IDX_LOBRDB_MAX, 28);
	validateConsecutive("Low-Wooden Bridge", SpecialOverlays::IDX_LOBRDG_MIN, SpecialOverlays::IDX_LOBRDG_MAX, 28);

	OverlayType* pHighWood = OverlayType::Array.get(SpecialOverlays::IDX_BRIDGEB1);
	OverlayType* pHighWood2 = OverlayType::Array.get(SpecialOverlays::IDX_BRIDGEB2);
	OverlayType* pHighConcrete = OverlayType::Array.get(SpecialOverlays::IDX_BRIDGE1);
	OverlayType* pHighConcrete2 = OverlayType::Array.get(SpecialOverlays::IDX_BRIDGE2);
	OverlayType* pHighTrack = OverlayType::Array.get(SpecialOverlays::IDX_RAILBRDG1);
	OverlayType* pHighTrack2 = OverlayType::Array.get(SpecialOverlays::IDX_RAILBRDG2);

	if (pHighWood && pHighWood->valid && !pHighWood->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_BRIDGEB1);
	if (pHighWood &&!pHighWood->valid) logNonExisting(SpecialOverlays::IDX_BRIDGEB1);

	if (pHighWood2 && pHighWood2->valid && !pHighWood2->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_BRIDGEB2);
	if (pHighWood2 &&!pHighWood2->valid) logNonExisting(SpecialOverlays::IDX_BRIDGEB2);

	if (pHighConcrete && pHighConcrete->valid && !pHighConcrete->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_BRIDGE1);
	if (pHighConcrete &&!pHighConcrete->valid) logNonExisting(SpecialOverlays::IDX_BRIDGE1);
	if (pHighConcrete2 && pHighConcrete2->valid && !pHighConcrete2->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_BRIDGE1);
	if (pHighConcrete2 &&!pHighConcrete2->valid) logNonExisting(SpecialOverlays::IDX_BRIDGE2);

	if (pHighTrack && pHighTrack->valid && !pHighTrack->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_RAILBRDG1);
	if (pHighTrack &&!pHighTrack->valid) logNonExisting(SpecialOverlays::IDX_RAILBRDG1);
	if (pHighTrack2 && pHighTrack2->valid && !pHighTrack2->Overrides)
		logHighBridgeError(SpecialOverlays::IDX_RAILBRDG2);
	if (pHighTrack2 &&!pHighTrack2->valid) logNonExisting(SpecialOverlays::IDX_RAILBRDG2);
}

void OverlayTypeValidator::logNonExisting(int index)
{
	dumpItAll = true;
	Log::line("OverlayType at index " + Log::toString(index)
		+ " is supposed to be a valid OverlayType! It is used in a hardcoded way by the game!", Log::DEBUG);
}

void OverlayTypeValidator::logHighBridgeError(int index)
{
	dumpItAll = true;
	Log::line("OverlayType at index " + Log::toString(index)
		+ " is supposed to have Overrides = yes! It is used for bridge drawing!", Log::DEBUG);
}

void OverlayTypeValidator::validateTracks()
{
	validateConsecutive("Track", SpecialOverlays::IDX_TRACKS_MIN, SpecialOverlays::IDX_TRACKS_MAX, 12);
}

void OverlayTypeValidator::validateVeinhole()
{
	OverlayType* pVeinMonster = OverlayType::Array.get(SpecialOverlays::IDX_VEINHOLE);
	OverlayType* pVeins = OverlayType::Array.get(SpecialOverlays::IDX_VEINS);
	OverlayType* pVeinDummy = OverlayType::Array.get(SpecialOverlays::IDX_VEINHOLEDUMMY);

	if (pVeinMonster && pVeinMonster->valid && (!pVeinMonster->IsVeinholeMonster || !pVeinMonster->IsVeins))
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_VEINHOLE)
			+ " is supposed to have IsVeinholeMonster = yes and IsVeins = yes! It is used for Veinhole logic!", Log::DEBUG);
	}

	if (pVeinDummy && pVeinMonster->valid  && !pVeinDummy->IsVeins)
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_VEINHOLEDUMMY)
			+ " is supposed to have IsVeins = yes! It is used for Veinhole logic!", Log::DEBUG);
	}


	if (pVeins && pVeinMonster->valid  && !pVeins->IsVeins)
	{
		dumpItAll = true;
		Log::line("OverlayType at index " + Log::toString((int)SpecialOverlays::IDX_VEINS)
			+ " is supposed to have IsVeins = yes! It is used for Veinhole logic!", Log::DEBUG);
	}
}

void OverlayTypeValidator::validateConsecutive(const std::string& name, int start, int end, int amount, bool isTiberium /* = false */)
{
	std::stringstream number;
	int index = start;

	for (unsigned int i = 0; i < amount; ++i)
	{
		if (i < 9)
			number << '0';
		number << i + 1;

		OverlayType* pOT = OverlayType::Array.get(index);

		std::string kek = pOT->ID.substr(pOT->ID.length() - 2, pOT->ID.length());

		if (kek != number.str())
		{
			dumpItAll = true;
			Log::line(name + " OverlayTypes should be consecutive in [OverlayTypes], starting from index "
				+ Log::toString(start) + " to "
				+ Log::toString(end) + ", this enumeration is broken!", Log::DEBUG);
			break;
		}

		if (isTiberium && !pOT->Tiberium)
		{
			Log::line(name + " OverlayTypes should have Tiberium = yes, this one doesn't!", Log::DEBUG);
		}

		number.str(std::string());
		++index;
	}
}

void OverlayTypeValidator::dumpOverlayTypes()
{
	if (!dumpItAll) return;

	Log::line();
	Log::line(" === PARSED DATA DUMP === ", Log::DEBUG);
	Log::line("One or more errors were found, therefore the entire OverlayTypes list will be dumped.", Log::DEBUG);
	Log::line("Use this list to compare it to the knowledge about OverlayTypes to fix the issue(s).", Log::DEBUG);
	OverlayType::Array.dumpContent();
}