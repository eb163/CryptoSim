#pragma once
#include "mvc\Event.h"
#include "SimRates.h"
class EventSpeedChange :
	public Event
{
private:
	SimRate rate;
	int modifier;

protected:

public:
	EventSpeedChange();
	~EventSpeedChange();

	SimRate getSimRate();
	void setSimRate(SimRate s);

	int getModifier();
};

