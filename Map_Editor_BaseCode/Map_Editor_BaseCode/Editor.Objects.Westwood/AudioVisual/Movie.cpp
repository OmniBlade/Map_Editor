#include "stdafx.h"
#include "Movie.h"

/* static */ WWList<Movie> Movie::Array;

Movie::Movie()
{
}

void Movie::parse(const std::string& id, const std::string& name)
{
	ID = name;
	Name = name;
}


