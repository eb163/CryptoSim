#pragma once

enum EventType {EVENT_CLOSE};

class Event
{
private:
	EventType type;

protected:
	void setType(EventType t);

public:
	EventType getType();
};