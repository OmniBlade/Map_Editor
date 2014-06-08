#pragma once
#include <string>
#include <memory>

class EventTemplate;
class LineSplitter;

class SubEvent
{
public:
	SubEvent();
	static std::shared_ptr<SubEvent> parse(LineSplitter& parts);
	void assignEventType();

	int eventType, parseType, param1;
	std::string param1S, param2;
	
	EventTemplate* pEventType;
};

