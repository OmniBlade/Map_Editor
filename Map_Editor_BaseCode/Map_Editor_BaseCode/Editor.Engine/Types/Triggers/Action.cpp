#include "stdafx.h"
#include "Action.hpp"

/* static */ ObjectList<Action> Action::Array;

Action::Action()
{
}

void Action::parse(const std::string& id, const std::string& list)
{
	ID = id;
}