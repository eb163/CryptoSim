#pragma once

enum EventType {EVENT_CLOSED, EVENT_RANDOMIZE};

class Event
{
private:
	EventType type;

protected:
	void setType(EventType t);

public:
	EventType getType();
};