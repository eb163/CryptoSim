#include "Network.h"

Network::Network()
{

}

Network::Network(DataManager* manager, int nodeCount)
{
	connectManager(manager);
	for (int i = 0; i < nodeCount; ++i)
	{
		addNewNode();
	}
}


Network::~Network()
{

}

void Network::connectManager(DataManager * m)
{
	manager = m;
}

void Network::addNewNode()
{
	Node n;
	string id = "Node " + std::to_string(nodes.size());
	n.setID(id);
	n.connectDataManager(manager);
	nodes.push_back(n);
	for (int i = 0; i < nodes.size() - 1; ++i)
	{
		nodes.at(nodes.size() - 1).addConnection(&nodes.at(i));
	}
}

Node* Network::getNode(int index)
{
	return &(nodes.at(index));
}

int Network::getSize()
{
	return nodes.size();
}
