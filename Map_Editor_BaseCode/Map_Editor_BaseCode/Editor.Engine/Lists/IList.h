#pragma once

#include <string>
#include <vector>

struct ListItem
{
	int Index;
	std::string Name;
	std::string ID;
	std::wstring DisplayName;
	ListItem(int index, const std::string& name, const std::string& id = "", const std::wstring& displayName = L"")
	:Index(index), Name(name), ID(id), DisplayName(displayName)
	{
		
	}
};

class IList
{
public:
	using value_type = ListItem;
	using List = std::vector<ListItem>;
	
	virtual ~IList() = default;

	virtual List getList() = 0;

protected:
	void add(List &ret, std::string name, int value = 0, std::string ID = "", std::wstring displayName = L"")
	{
		ret.emplace_back(value, name, ID, displayName);
	};

	void add(List &ret, value_type& item) 
	{
		ret.emplace_back(item.Index, item.Name, item.ID, item.DisplayName);
	};

	void optional_none(List &ret, bool allowed)
	{
		if (allowed)
		{
			add(ret, "<none>", -1);
		}
	};
};