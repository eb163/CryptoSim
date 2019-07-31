#pragma once
#include "mvc\Event.h"
#include "SimRates.h"
class EventSpeedChange :
	public Event
{
private:
	SimRate rate;
	int modifier;

	void setSimRate(SimRate s);

protected:

public:
	EventSpeedChange(SimRate s);
	~EventSpeedChange();

	SimRate getSimRate();

	int getModifier();
};

