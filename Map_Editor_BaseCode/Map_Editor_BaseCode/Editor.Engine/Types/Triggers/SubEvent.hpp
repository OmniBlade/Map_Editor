#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../../../Editor.FileSystem/MapFile/ParamContent.h"

class EventType;
class LineSplitter;

class SubEvent
{
public:
	SubEvent();
	static std::shared_ptr<SubEvent> parse(LineSplitter& parts);
	void assignEventType();

	std::string asString();
	std::string paramAsString(int paramNumber);

	int eventType = 0, parseType = 0;
	std::vector<ParamContent> params;
	
	EventType* pEventType;
};

