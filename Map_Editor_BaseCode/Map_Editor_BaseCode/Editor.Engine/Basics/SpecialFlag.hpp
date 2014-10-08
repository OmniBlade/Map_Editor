#pragma once

class INIFile;

class SpecialFlag
{
public:
	static SpecialFlag* instance();
	static void writeToINI(INIFile& file);

	void parse();

	bool TiberiumGrows, TiberiumSpreads, TiberiumExplosive, DestroyableBridges, MCVDeploy, InitialVeteran, FixedAlliance;
	bool HarvesterImmune, FogOfWar, Inert, IonStorms, Meteorites, Visceroids, EscapeMovies;
	
private:
	static SpecialFlag* it;
	SpecialFlag();

	/*
	TiberiumGrows=yes
	TiberiumSpreads=yes
	TiberiumExplosive=no
	DestroyableBridges=yes
	MCVDeploy=no
	InitialVeteran=no
	FixedAlliance=no
	HarvesterImmune=no
	FogOfWar=no
	Inert=no
	IonStorms=no
	Meteorites=no
	Visceroids=no
	EscapeMovies=yes --> default!
	*/
};

