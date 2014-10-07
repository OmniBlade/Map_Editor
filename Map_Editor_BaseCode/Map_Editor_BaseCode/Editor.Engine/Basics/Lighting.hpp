#pragma once

class INIFile;

class Lighting
{
public:
	static Lighting* instance();
	static void writeToINI(INIFile& file);

	void parse();


	//Normal lighting
	float Red, Green, Blue, Ambient, Ground, Level;
	//Lightning Storm
	float IonRed, IonGreen, IonBlue, IonAmbient, IonGround, IonLevel;
	//Dominator
	float DomRed, DomGreen, DomBlue, DomAmbient, DomGround, DomLevel, DomChangeRate;
	//Nuke change rate
	float NukeChangeRate;

private:
	static Lighting* it;
	Lighting();

};

