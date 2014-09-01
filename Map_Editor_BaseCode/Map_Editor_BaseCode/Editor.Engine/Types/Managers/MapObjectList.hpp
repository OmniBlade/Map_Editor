#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../../../Log.hpp"

template <typename T> class MapObjectList
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

		objectTypeList.push_back(std::make_unique<T>(name));
		return objectTypeList.back().get();
	}


	int findIndex(const std::string& name) const
	{
		auto it = std::find_if(objectTypeList.begin(), objectTypeList.end(), [&](const std::unique_ptr<T>& ptr)
		{
			return !_strcmpi(ptr->ID.c_str(), name.c_str());
		});

		if (it != objectTypeList.end())
			return std::distance(objectTypeList.begin(), it);
		else
			return -1;
	}

	unsigned int count()
	{
		return objectTypeList.size();
	}

	T* get(unsigned int index)
	{
		return objectTypeList[index].get();
	}

	/*
		Winner of the Ugliest Function / Hack of 2014 ©
	*/
	void make()
	{
		objectTypeList.push_back(std::make_unique<T>());
	}

	void createOverlay(int x, int y, int index, int frame)
	{
		objectTypeList.push_back(std::make_unique<T>(x, y, index, frame));
	}

	std::vector<std::unique_ptr<T>> objectTypeList;
	int lastParsedItem = 0;
};