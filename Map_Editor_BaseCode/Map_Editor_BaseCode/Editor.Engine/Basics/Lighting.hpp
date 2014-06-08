#pragma once
class Lighting
{
public:
	Lighting();
	~Lighting();

	//Normal lighting
	float red, green, blue, ambient, ground, level;
	//Lightning Storm
	float ionRed, ionGreen, ionBlue, ionAmbient, ionGround, ionLevel;
	//Dominator
	float domRed, domGreen, domBlue, domAmbient, domGround, domLevel, domChangeRate;
	//Nuke change rate
	float nukeChangeRate;

};

