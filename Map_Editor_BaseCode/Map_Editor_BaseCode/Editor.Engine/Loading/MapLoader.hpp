#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.Objects.Westwood/General/General.hpp"
#include "../../Editor.Objects.Westwood/General/AI.hpp"
#include "../../Editor.Objects.Westwood/General/SpecialWeapon.hpp"
#include "../../Editor.Objects.Westwood/General/AudioVisual.hpp"
#include "../../Editor.Objects.Westwood/General/CombatDamage.hpp"

class MapLoader
{
public:
	MapLoader();
	void allocateMainRules(INIFile* file, INIFile* art);
	void loadAll(INIFile* file, INIFile* art);
	void loadArtAll(INIFile* art);
	void insertNukePayload();
	void insertDAnimation();

private:
	General* general;
	AI* ai;
	SpecialWeapon* specialWeapons;
	AudioVisual* audioVisual;
	CombatDamage* combatDamage;
};

