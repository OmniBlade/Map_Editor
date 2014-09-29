#pragma once

#include <vector>
#include <memory>
#include "IList.h"

class ScriptType;

class ListProvider
{
public:
	static ListProvider* getProvider();
	std::vector<ListItem> getListFor(int param, ScriptType* scr = nullptr);

	/*
		This function allows for multiple lists combined
		An example would be Countries and special Multiplayer Countries (<Player @ X> etc.) which are all valid,
		but for the sake of overview there won't be an additional list made available in the typeLists vector
		NOTE: Second item in the params vector will be added AFTER the first item (same goes for every entry)

		@param params The list of params used to get the lists for (AKA List Types, see PARAMS file)
		@return The list of all combined items
	*/
	std::vector<ListItem> getCombinedList(std::vector<int> params);

private:
	static ListProvider* provider;
	ListProvider();

	void fillListVector();

	static std::vector<std::shared_ptr<IList>> typeLists;
};
