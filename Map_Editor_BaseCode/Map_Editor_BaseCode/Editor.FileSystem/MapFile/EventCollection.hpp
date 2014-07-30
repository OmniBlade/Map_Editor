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
	int count;
	const int YRCount = 62; // 0 - 61...
	std::vector<std::unique_ptr<EventTemplate>> eventList;
};


