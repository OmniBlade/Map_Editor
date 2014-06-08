#include "EventTemplate.hpp"
#include <vector>
#include <memory>

class EventCollection
{
public:
	static EventCollection* getInstance();

	void parse();
	EventTemplate* get(int id);

private:
	static EventCollection* instance;
	EventCollection();

	int count;
	const int YRCount = 62; // 0 - 61...
	std::vector<std::unique_ptr<EventTemplate>> eventList;
};


