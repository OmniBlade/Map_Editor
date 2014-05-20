#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.Objects.Westwood/General/General.hpp"
#include "../../Editor.Objects.Westwood/General/AI.hpp"
#include "../../Editor.Objects.Westwood/General/SpecialWeapon.hpp"
#include "../../Editor.Objects.Westwood/General/AudioVisual.hpp"
#include "../../Editor.Objects.Westwood/General/CombatDamage.hpp"
#include "../../Editor.Objects.Westwood/General/Side.hpp"
#include "../../Editor.Objects.Westwood/General/IQ.hpp"

class MapLoader
{
public:
	MapLoader();
	void load(INIFile* file);
	/*
		Allocates the main rules data as presented by DCoder (used to create proper lists)
		@param file The rules / map file to parse
	*/
	void allocateMainRules(INIFile* file);

	/*
		Loads the rules (and art) data as presented by DCoder (used to fill proper lists)
		@param file The rules / map file to parse
		@param art The artmd.ini file (always the same!)
	*/
	void loadAll(INIFile* file);

	/*
		Extremely debug, if you want to call this function and poop something out,
		add the list to the function, there's no argument what so ever
	*/
	void dumpLists();

	/*
		Inserts the hardcoded NukePayload entry in the WeaponTypes list
		NukePayload is not referenced anywhere in a Weapon tag in rulesmd.ini, thus no other option was possible
	*/
	void insertNukePayload();

	/*
		Inserts the mysterious "D" animation in the Animations list
		"D" isn't referenced ANYwhere, which leads to believe it's a redundant hardcoded entry from Westwood
		This entry always comes after [Animations] is loaded
	*/
	void insertDAnimation();

private:
	General* general;
	AI* ai;
	SpecialWeapon* specialWeapons;
	AudioVisual* audioVisual;
	CombatDamage* combatDamage;
	Side* sides;
	IQ* iq;
};

