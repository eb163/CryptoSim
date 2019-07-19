#include "Driver.h"



Driver::Driver()
{
}


Driver::~Driver()
{
}

void Driver::setSimRate(time_t rate)
{
}

time_t Driver::getSimRate()
{
	return simRate;
}

void Driver::setTimeSinceLastAction(time_t time)
{
}

void Driver::modifyTimeSinceLastAction(time_t deltaTime)
{
	timeSinceLastAction += deltaTime;
}

time_t Driver::getTimeSinceLastAction()
{
	return timeSinceLastAction;
}
