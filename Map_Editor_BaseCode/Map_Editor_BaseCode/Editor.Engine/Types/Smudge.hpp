#pragma once
#include <string>
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
#include "Managers\ObjectList.hpp"

class SmudgeType;

class Smudge
{
public:
	static ObjectList<Smudge> Array;

	Smudge();
	void parse(const std::string& id, const std::string& list);

	int unknown;
	std::string smudge;
	Vector2D loc;
	SmudgeType* pSmudgeType;
};

