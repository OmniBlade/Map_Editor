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

		objectList.push_back(std::make_unique<T>(name));
		return objectList.back().get();
	}


	int findIndex(const std::string& name) const
	{
		auto it = std::find_if(objectList.begin(), objectList.end(), [&](const std::unique_ptr<T>& ptr)
		{
			return !_strcmpi(ptr->ID.c_str(), name.c_str());
		});

		if (it != objectList.end())
			return std::distance(objectList.begin(), it);
		else
			return -1;
	}

	unsigned int count()
	{
		return objectList.size();
	}

	T* get(unsigned int index)
	{
		return objectList[index].get();
	}

	/*
		Winner of the Ugliest Function / Hack of 2014 ©
	*/
	void make()
	{
		objectList.push_back(std::make_unique<T>());
	}

	void createOverlay(int x, int y, int index, int frame)
	{
		objectList.push_back(std::make_unique<T>(x, y, index, frame));
	}

	std::vector<std::string> getIDOfLocalObjects()
	{
		std::vector<std::string> ret;
		for (auto& it : objectList)
		{
			if (!it->isGlobal)
				ret.push_back(it->ID);
		}
		return ret;
	}

	std::vector<std::unique_ptr<T>> objectList;
	int lastParsedItem = 0;
};