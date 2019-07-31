#include "EventSpeedChange.h"

EventSpeedChange::EventSpeedChange(SimRate s)
{
	setType(EventType::EVENT_SPEEDCHANGE);
	setSimRate(s);
}

EventSpeedChange::~EventSpeedChange()
{

}

SimRate EventSpeedChange::getSimRate()
{
	return rate;
}

void EventSpeedChange::setSimRate(SimRate s)
{
	rate = s;
	if(rate == SimRate::PAUSE)
	{
		modifier = 0;
	}
	else if (rate == SimRate::SPEED)
	{
		modifier = 3;
	}
	else if (rate == SimRate::SLOW)
	{
		modifier = -3;
	}
}

int EventSpeedChange::getModifier()
{
	return modifier;
}
