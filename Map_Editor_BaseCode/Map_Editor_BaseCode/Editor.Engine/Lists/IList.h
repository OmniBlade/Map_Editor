#pragma once

#include <string>
#include <vector>

struct ListItem
{
	int Index;
	std::string Name;
	std::string ID;
	std::wstring DisplayName;
	bool valid;
	ListItem(int index, const std::string& name, const std::string& id = "", bool isValid = true, const std::wstring& displayName = L"")
		:Index(index), Name(name), ID(id), DisplayName(displayName), valid(isValid)
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
	void add(List &ret, std::string name, int value = 0, std::string ID = "", bool isValid = true, std::wstring displayName = L"")
	{
		ret.emplace_back(value, std::move(name), std::move(ID), isValid, std::move(displayName));
	};

	void add(List &ret, value_type& item)
	{
		ret.push_back(item);
	};

	void optional_none(List &ret, bool allowed)
	{
		if (allowed)
		{
			add(ret, "<none>", -1);
		}
	};
};