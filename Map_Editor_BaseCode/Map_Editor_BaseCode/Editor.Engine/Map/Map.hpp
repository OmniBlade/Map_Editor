#pragma once
#include <vector>
#include <memory>

#include "Cells\CellClass.h"

class Map
{
public:
	static Map* instance();

	void setupCells();

private:
	Map();
	static Map* pInstance;


	std::vector<CellClass> cells;
};

