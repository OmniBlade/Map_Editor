#include "EventType.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class EventCollection
{
public:
	static EventCollection* getInstance();

	void parse(ParamCollection* paramColl);
	EventType* get(int id);

private:
	static EventCollection* instance;
	EventCollection();

	ParamCollection* paramColl;
	int rExpCount, rBaseCount, count;
	const int BaseCount = 0x3B;
	const int ExpCount = 0x3E;
	std::vector<std::unique_ptr<EventType>> eventList;
};


