#include "stdafx.h"
#include "List.hpp"
#include <iostream>
#include "../../Log.hpp"

//template<class a_type> void a_class<a_type>::a_function()

template<typename T> void List<T>::find(const std::string& name)
{
	auto index = findIndex(name);
	return (index >= 0) ? get(index) : nullptr;
}

template<typename T> void List<T>::findOrAllocate(const std::string& name)
{
	if (auto ptr = find(name))
		return ptr;

	auto it = typeList.emplace_back(name);
	return (*it)->get();
}

template<typename T> int List<T>::findIndex(const std::string& name) const 
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

template<typename T> unsigned int List<T>::count()
{
	return typeList.size();
}

template<typename T> T* List<T>::get(unsigned int index)
{
	return TypeList[index].get()
}

template<typename T> void List<T>::findOrAllocateAll(List<T>* list, INISection* section) 
{
	for (const auto& it : section) 
	{
		list.FindOrAllocate(it->second);
	}
}