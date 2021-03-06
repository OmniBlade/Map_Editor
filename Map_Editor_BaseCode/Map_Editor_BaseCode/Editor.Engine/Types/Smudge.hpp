#pragma once
#include <string>
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
#include "Managers\MapObjectList.hpp"

class SmudgeType;
class INIFile;

class Smudge
{
public:
	static MapObjectList<Smudge> Array;
	static void writeToINI(INIFile& file);

	Smudge();
	void parse(const std::string& id, const std::string& list);
	std::string asString();

	int unknown;
	std::string smudge;
	Vector2D loc;
	SmudgeType* pSmudgeType;
};

