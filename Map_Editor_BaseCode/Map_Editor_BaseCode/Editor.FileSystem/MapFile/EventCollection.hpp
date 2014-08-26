#include "EventTemplate.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class EventCollection
{
public:
	static EventCollection* getInstance();

	void parse(ParamCollection* paramColl);
	EventTemplate* get(int id);

private:
	static EventCollection* instance;
	EventCollection();

	ParamCollection* paramColl;
	int rExpCount, rBaseCount, count;
	const int BaseCount = 59; // 0 - 58...
	const int ExpCount = 62; // 0 - 61...
	std::vector<std::unique_ptr<EventTemplate>> eventList;
};


