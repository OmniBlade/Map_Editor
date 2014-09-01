#pragma once

#include <vector>
#include <memory>
#include "IList.h"

class ListProvider
{
public:
	ListProvider();

	std::vector<ListItem> getListFor(int param);

private:
	void fillListVector();

	static std::vector<std::shared_ptr<IList>> typeLists;
};
