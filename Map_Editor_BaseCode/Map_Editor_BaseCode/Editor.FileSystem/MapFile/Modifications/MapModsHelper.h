template<typename T>
void fillMapSection(MapMods* mods, MapObjectList<T>& list)
{
	mods->addSections(list.getIDOfLocalObjects());
}

template<typename T>
void fillMapSection(MapMods* mods, WWList<T>& list)
{
	mods->addSections(list.getIDOfLocalObjects());
}