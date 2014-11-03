#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../../Log.hpp"

template <typename T> class WWList
{
public:
	/*
		Finds the object type specified in the parameter and returns a pointer to it
		@param name The ID of the object
		@return A pointer to the object if it is found, otherwise nullptr is returned
	*/
	T* find(const std::string& name)
	{
		auto index = findIndex(name);
		return (index >= 0) ? get(index) : nullptr;
	}
	
	/*
		Some fun stuff from the game; it either finds the object with the specified ID,
		or it creates it
		@param name The ID of the object
		@return A pointer to the object, nullptr if explicitly specified there is nothing in the name
	*/
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
				Log::line("V - " + Log::toString(i) + " = " + typeList[i]->ID, Log::EXTRA);
			if (!typeList[i]->valid)
				Log::line("X - " + Log::toString(i) + " = " + typeList[i]->ID, Log::EXTRA);
		}
	}

	bool exists(const std::string& ID)
	{
		for (const auto& it : typeList)
		{
			if (it->ID == ID)
			{
				return true;
			}
		}
		return false;

		for (unsigned int i = 0; i < typeList.size(); ++i)
		{
			if (typeList[i]->ID == ID)
				return true;
		}
		return false;
	}

	void make()
	{
		typeList.push_back(std::make_unique<T>());
	}
	
	void clear()
	{
		typeList.clear();
		lastLoaded = typeList.size();
	}

	std::vector<std::string> getIDOfLocalObjects()
	{
		std::vector<std::string> ret;
		for (auto& it : typeList)
		{
			ret.push_back(it->ID);
		}
		return ret;
	}

	int lastLoaded = 0;
	std::vector<std::unique_ptr<T>> typeList;
};

