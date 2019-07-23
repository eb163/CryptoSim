#pragma once
#include <vector>
#include "Node.h"
#include "DataManager.h"

class Network
{
private:
	vector<Node> nodes;
	DataManager* manager;


public:
	Network();
	Network(DataManager* manager, int nodeCount);
	~Network();

	void connectManager(DataManager* m);

	void addNewNode();
	Node* getNode(int index);
	int getSize(); //returns how many nodes exist in the network
};

