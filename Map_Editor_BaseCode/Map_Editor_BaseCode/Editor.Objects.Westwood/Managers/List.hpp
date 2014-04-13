#pragma once

#include <vector>
#include <memory>
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

template <typename T> class List
{
public:
	void find(const std::string& name);
	int findIndex(const std::string& name) const;
	void findOrAllocate(const std::string& name);
	unsigned int count();
	T* get(unsigned int index);

	void findOrAllocateAll(List<T>* list, INISection* section);

	std::vector<std::unique_ptr<T>> typeList;
};

