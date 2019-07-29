#pragma once
#include <ctime>
#include <cstdlib> //for srand() and rand()
#include "Network.h"

enum Action {DO_NOTHING = 0, ADD_TRANSACTION = 1};

class Driver
{
private:
	time_t simRate;
	time_t timeSinceLastAction;

	Network* nw;
	DataManager* manager = nullptr;

	//list of actions which the Driver can take to operate on the Network of Nodes
	//how to implement?
	int numberOfActions = 2;

public:
	Driver();
	~Driver();

	void connectDataManager(DataManager* m);
	void connectNetwork(Network* n);

	void setSimRate(time_t rate);
	time_t getSimRate();

	void setTimeSinceLastAction(time_t time);
	void modifyTimeSinceLastAction(time_t deltaTime);
	time_t getTimeSinceLastAction();

	void pollForAction();

	void takeAction();

	//actions which the Driver can perform on the nodes of the network
	void addTransaction(); //currently just adds a block containing a string of data
};
