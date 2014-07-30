#include "stdafx.h"
#include "ValidatorHelper.h"
#include "../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../Editor.Objects.Westwood/Types/Animation.hpp"

ValidatorHelper::ValidatorHelper()
{
}

/* static */ bool ValidatorHelper::checkParam(int paramID, const std::string& value)
{
	switch (paramID)
	{
	default:
	case 0:
		return true;
	case 1:
		return checkParam(paramID, atoi(value.c_str()));
	case 2:
		return checkParam(paramID, atoi(value.c_str()));
	case 3:
		return checkParam(paramID, atoi(value.c_str()));
	}
	return false;
}

/* static */ bool ValidatorHelper::checkParam(int paramID, int value)
{
	return false;
}