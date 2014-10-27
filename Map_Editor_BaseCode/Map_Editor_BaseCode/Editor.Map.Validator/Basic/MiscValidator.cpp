#include "stdafx.h"
#include "MiscValidator.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"

#include "../../Editor.Engine/Types/Smudge.hpp"
#include "../../Editor.Engine/Types/Tube.hpp"
#include "../../Editor.Engine/Types/Waypoint.hpp"
#include "../../Editor.Engine/Types/VariableName.hpp"

MiscValidator::MiscValidator()
{
	//Locals
	//validateLocals();
	//Log::finishErrorRound();
	//Log::finishWarningRound();
	//Smudges
	validateSmudge();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Tubes
	validateTube();
	Log::finishErrorRound();
	Log::finishWarningRound();
	//Waypoints
	validateWaypoint();
	Log::finishErrorRound();
	Log::finishWarningRound();
}

MiscValidator::~MiscValidator()
{
}

void MiscValidator::validateWaypoint()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Waypoints] now...", Log::INFO);
	for (const auto& it : Waypoint::Array.objectList)
	{
		if (it->index < 0 || it->index > 701)
			Log::validatorLine("Waypoint with ID '" + it->ID + "' has an invalid index set.", Log::ERROR_BUFFER);
		if (it->MapCoords.X < 0)
			Log::validatorLine("Waypoint with ID '" + it->ID + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		if (it->MapCoords.Y < 0)
			Log::validatorLine("Waypoint with ID '" + it->ID + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
	}
}

void MiscValidator::validateLocals()
{
	for (const auto& it : VariableName::Array.objectList)
	{

	}
}

void MiscValidator::validateTube()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Tubes] now...", Log::INFO);
	for (const auto& it : Tube::Array.objectList)
	{
		const std::string& oppositeID = getOppositeTube(it.get());
		if (oppositeID == "")
			Log::validatorLine("Tube at index '" + it->ID + "' has no opposite Tube set.", Log::WARNING_BUFFER);
		walkTubePath(it.get());
	}
}

void MiscValidator::validateSmudge()
{
	Log::validatorLine();
	Log::validatorLine("Validating [Smudge] now...", Log::INFO);
	unsigned int index = 0;
	for (const auto& it : Smudge::Array.objectList)
	{
		if (!it->pSmudgeType)
			Log::validatorLine("Smudge at index '" + Log::toString(index) + "' has an invalid SmudgeType set.", Log::ERROR_BUFFER);
		if (it->loc.x < 0)
			Log::validatorLine("Smudge at index '" + Log::toString(index) + "' has an invalid X-coordinate set.", Log::ERROR_BUFFER);
		if (it->loc.y < 0)
			Log::validatorLine("Smudge at index '" + Log::toString(index) + "' has an invalid Y-coordinate set.", Log::ERROR_BUFFER);
		if (it->unknown != 0)
			Log::validatorLine("Smudge at index '" + Log::toString(index) + "' has an invalid Unknown index set (should always be 0).", Log::ERROR_BUFFER);
		index++;
	}
}

std::string const& MiscValidator::getOppositeTube(Tube* tube)
{
	for (const auto& it : Tube::Array.objectList)
	{
		if (it->startX == tube->endX && it->startY == tube->endY && it->endX == tube->startX && it->endY == tube->startY)
		{
			return it->ID;
		}
	}

	static std::string null;
	return null;
}

void MiscValidator::walkTubePath(Tube* tube)
{
	int tubeSize = tube->steps.size();
	int tubePosX = 0, tubePosY = 0;
	bool tubeEnded = false, logError = true;

	for (int i = 0; i < tubeSize; ++i)
	{
		int currentDirection = tube->steps[i];

		switch (currentDirection)
		{
		case -1:
			tubeEnded = true;
			break;
		case 0:
			tubePosY--;
			break;
		case 1:
			tubePosY--;
			tubePosX++;
			break;
		case 2:
			tubePosX++;
			break;
		case 3:
			tubePosY++;
			tubePosX++;
			break;
		case 4:
			tubePosY++;
			break;
		case 5:
			tubePosY++;
			tubePosX--;
			break;
		case 6:
			tubePosX--;
			break;
		case 7:
			tubePosY--;
			tubePosX--;
			break;
		}


		if (i > 99 && !tubeEnded)
		{
			Log::validatorLine("Tube at index '" + tube->ID + "' has no more than 94 directions set Tube set.", Log::WARNING_BUFFER);
			tubeEnded = true;
			logError = false;
		}

		if (tubeEnded)
		{//Tube ended, verify positions
			if ((tube->startX + tubePosX != tube->endX || tube->startY + tubePosY > tube->endY) && logError)
			{
				Log::validatorLine("Tube at index '" + tube->ID + "' has a path that does not correspond with the starting and ending coordinates.", Log::ERROR_BUFFER);
			}
			break;
		}
	}
}