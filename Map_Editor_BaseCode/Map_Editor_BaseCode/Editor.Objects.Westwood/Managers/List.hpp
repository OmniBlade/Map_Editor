#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../../Log.hpp"

template <typename T> class List
{
public:
	T* find(const std::string& name)
	{
		auto index = findIndex(name);
		return (index >= 0) ? get(index) : nullptr;
	}

	T* findOrAllocate(const std::string& name)
	{
		int ret1 = _strcmpi("", name.c_str());
		int ret2 = _strcmpi("none", name.c_str());
		int ret3 = _strcmpi("<none>", name.c_str());

		if (ret1 == 0 || ret2 == 0 || ret3 == 0)
			return nullptr;

		if (auto ptr = find(name))
			return ptr;

		typeList.push_back(std::make_unique<T>(name));
		return typeList.back().get();
	}

	int findIndex(const std::string& name) const
	{
		auto it = std::find_if(typeList.begin(), typeList.end(), [&](const std::unique_ptr<T>& ptr)
		{
			return !_strcmpi(ptr->ID.c_str(), name.c_str());
		});

		if (it != typeList.end())
			return std::distance(typeList.begin(), it);
		else
			return -1;
	}

	unsigned int count()
	{
		return typeList.size();
	}

	T* get(unsigned int index)
	{
		return typeList[index].get();
	}

	void dumpContent()
	{
		for (unsigned int i = 0; i < typeList.size(); ++i)
		{
			if (typeList[i]->valid)
				Log::note(typeList[i]->ID + " - valid", Log::DEBUG);
			else
				Log::note(typeList[i]->ID + " - invalid", Log::DEBUG);
		}
	}

	std::vector<std::unique_ptr<T>> typeList;
};

