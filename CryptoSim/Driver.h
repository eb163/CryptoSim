#pragma once
#include <ctime>
class Driver
{
private:
	time_t simRate;
	time_t timeSinceLastAction;

	//list of actions which the Driver can take to operate on the Network of Nodes
	//how to implement?

public:
	Driver();
	~Driver();

	void setSimRate(time_t rate);
	time_t getSimRate();

	void setTimeSinceLastAction(time_t time);
	void modifyTimeSinceLastAction(time_t deltaTime);
	time_t getTimeSinceLastAction();
};

